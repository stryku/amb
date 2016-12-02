from subprocess import call
call(["cloc", ".", "--exclude-dir=tmp,resources,releases,cmake,build,bin"])