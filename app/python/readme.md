# python document
    [docs](https://docs.python.org/3/)
    pypi, tox

# data integrity
    ```
    python -c "import hashlib, sys;pritn hashlib.sha1(open(sys.argv[1], 'rb').read()).hexdigest()"  file

    # linux bash
    echo "b3c0acde4e02b6feb3602d4c037100222caa538f  merge_sort.o" | sha1sum -c -

    # windows powershell
    Get-FileHash -Algorithm SHA1 .\start_up.bat

    # windows cmd
    certutil -hashfile file SHA1
    fciv.exe # file checksum and integrity verifier
    ```
