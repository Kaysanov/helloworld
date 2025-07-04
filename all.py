
import os

def merge_files(directory, output_file, extensions=None):
    with open(output_file, 'w', encoding='utf-8') as outfile:
        for root, _, files in os.walk(directory):
            for file in files:
                if extensions and not file.endswith(tuple(extensions)):
                    continue
                path = os.path.join(root, file)
                try:
                    with open(path, 'r', encoding='utf-8') as infile:
                        outfile.write(f"\n\n/* ---- {path} ---- */\n\n")
                        outfile.write(infile.read())
                except UnicodeDecodeError:
                    print(f"Skipped binary file: {path}")

# Пример использования
merge_files('./', 'combined.txt', ('.txt', '.h', '.cpp'))