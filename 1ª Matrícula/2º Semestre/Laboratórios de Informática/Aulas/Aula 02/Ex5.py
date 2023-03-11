import os
import sys
import subprocess


def listdir():
    if len(sys.argv) != 3:
        print("Usage: python listdir.py <directory_path> <ignore_term>")
        sys.exit(1)

    directory_path = sys.argv[1]
    ignore_term = sys.argv[2]


def test_invalid_arguments(directory_path, ignore_term):
    try:
        output = subprocess.check_output(["ls", "-la", directory_path], universal_newlines=True)
        lines = output.split("\n")
        filtered_lines = [line for line in lines if ignore_term not in line]
        print("\n".join(filtered_lines))
    except subprocess.CalledProcessError:
        print("Error: could not list directory.")
        sys.exit(1)


def test_nonexisting_directory(directory_path, ignore_term):
    if not os.path.isdir(directory_path):
        print("Error: directory does not exist.")
        sys.exit(1)

    try:
        output = subprocess.check_output(["ls", "-la", directory_path], universal_newlines=True)
        lines = output.split("\n")
        filtered_lines = [line for line in lines if ignore_term not in line]
        print("\n".join(filtered_lines))
    except subprocess.CalledProcessError:
        print("Error: could not list directory.")
        sys.exit(1)


def test_ignore_term():
    with open("test.txt", "w") as f:
        f.write("file1\nfile2\nignoreme.txt\n")

    result = subprocess.run(["python", "listdir.py", ".", "ignoreme"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    assert result.returncode == 0
    assert b"ignoreme.txt" not in result.stdout
    assert b"file1\nfile2" in result.stdout

    os.remove("test.txt")
