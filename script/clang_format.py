#!/usr/bin/env python

import argparse
import glob
import os
import subprocess
import xml.etree.ElementTree as ET


def replacements_from_file(file, style="file", executable="clang-format"):
    replacements = []

    clang_format_args = [executable]
    clang_format_args.append("-style={}".format(style))
    clang_format_args.append("-output-replacements-xml")
    clang_format_args.append(os.path.basename(file))
    replacement_xml = subprocess.check_output(clang_format_args,
                                              cwd=os.path.dirname(file))
    replacement_xml_root = ET.XML(replacement_xml)
    for replacement_item in replacement_xml_root.findall('replacement'):
        replacements.append({
            "offset": int(replacement_item.attrib["offset"]),
            "length": int(replacement_item.attrib["length"]),
            "text": replacement_item.text,
        })

    return replacements


def errors_from_replacements(file, replacements=[]):
    errors = []

    lines = [0]  # line index to character offset
    file_content = ""
    for line in open(file, "r"):
        file_content += line
        lines.append(lines[-1] + len(line))

    for line_index, line_offset in enumerate(lines[:-1]):
        while (len(replacements) > 0 and
               lines[line_index + 1] > replacements[0]['offset']):
            replacement = replacements.pop(0)
            errors.append({
                "line": line_index + 1,
                "column": replacement['offset'] - line_offset + 1,
                "found": file_content[
                    replacement['offset']:replacement['offset'] +
                    replacement['length']],
                "expected": replacement['text'] if replacement['text'] else "",
            })

        if len(replacements) == 0:
            break

    return errors


def check_format(files=[], style="file", executable="clang-format"):
    executable = os.path.normpath(executable)
    total_error_count = 0
    file_errors = dict()
    print("Collected {} file(s) to check.".format(len(files)))

    for f in files:
        replacements = replacements_from_file(f, style, executable)
        errors = errors_from_replacements(f, replacements)
        if len(errors) > 0:
            print("- Checking {} ... {} format error{}"
                  .format(f, len(errors), 's' if len(errors) > 1 else ''))
            file_errors[f] = errors
            total_error_count += len(errors)
        else:
            print("- Checking {} ... OK".format(f))

    if total_error_count == 0:
        print("No format errors found.")
    else:
        print("A total of {} format error(s) found.".format(total_error_count))
        print("The following file(s) must be fixed:")
        for f in file_errors:
            print("- {}".format(f))
        print("Run clang-format to fix all format errors.")

    return total_error_count, file_errors


def run_format(files=[], style="file", executable="clang-format"):
    executable = os.path.normpath(executable)
    print("Collected {} file(s) to format.".format(len(files)))

    for f in files:
        clang_format_with_args = [executable]
        clang_format_with_args.append("-style={}".format(style))
        clang_format_with_args.append("-i")
        clang_format_with_args.append(os.path.basename(f))
        print("- Formatting {}".format(f))
        output = subprocess.check_output(clang_format_with_args,
                                         cwd=os.path.dirname(f))
        if len(output) > 0:
            print(output)


def check_clang_format_exe(executable="clang-format"):
    executable = os.path.normpath(executable)
    try:
        subprocess.check_output([executable, "--version"], shell=True)
        return True
    except subprocess.CalledProcessError:
        # Some versions of clang-format --version lead to non-zero exit status
        return True
    except OSError:
        return False


def main():
    parser = argparse.ArgumentParser(
        description="Check C/C++ formatting using clang-format")

    parser.add_argument('-c', '--check',
                        action='store_true',
                        help="Check the files instead of formatting them.")

    parser.add_argument("-s", "--style",
                        default="file",
                        help="Coding style, pass-through to clang-format's "
                        "-style=<string>, (default is '%(default)s').")

    parser.add_argument("-e", "--executable",
                        default="clang-format",
                        help="Path of clang-format if it's not added to PATH.")

    parser.add_argument("file", nargs="+",
                        help="Path(s) to the file(s) that will be checked "
                             "(wildcards and folders are accepted).")

    args = parser.parse_args()

    # Add double quotes around inline style
    if len(args.style) > 0 and args.style[0] == "{":
        args.style = "\"" + args.style + "\""

    # Make sure that clang-format executable is available
    if not check_clang_format_exe(args.executable):
        print("Cannot run 'clang-format'. Please make sure the provided "
              "executable is valid or `clang-format` can be reached in PATH.")
        exit(-1)

    # Collect files
    collected_files = set()
    for path in args.file:
        # If a folder is specified, collect all files from that folder
        if os.path.isdir(path):
            path = os.path.join(path, '*.*')
        for f in glob.iglob(path):
            collected_files.add(os.path.abspath(f))
    # Sort collected files alphabetically
    collected_files = list(collected_files)
    collected_files.sort()

    error_count = 0
    if args.check:
        error_count, file_errors = check_format(files=collected_files,
                                                style=args.style,
                                                executable=args.executable)
    else:
        run_format(files=collected_files,
                   style=args.style,
                   executable=args.executable)
    exit(error_count)


if __name__ == "__main__":
    main()
