'''Script for arduinofy repository '''

from os import path, remove
from shutil import move
from sys import argv

metadata_files_src_dst = {
    'keywords.txt' : ('meta', ''),
    'library.properties': ('meta', ''),
}

delete_folders = [
    'include',
    'meta',
    'test'
]

if not path.exists('.git'):
    print('CWD is not repository')
    exit()

for file, (src, dst) in metadata_files_src_dst.items():
    src_path = path.join(src, file)
    if not path.isfile(src_path):
        print(f'Error: {src_path} not found.')
        continue

    dst_path = path.join(dst, file)
    try:
        move(src_path, dst_path)
    except:
        print(f'There was an error moving the file {file}')
        continue
    print(f'{file} : {src} {dst}')

for folder in delete_folders:
    if not path.isdir(folder):
        print(f'{folder} was not found')
        continue
    remove(folder)

print('To restore, run git restore ./')
#remove(argv[0])
