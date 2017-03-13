[Reset your Master Password if you've forgotten it](chrome://pippki/content/resetpassword.xul)

# books
1. debugging
    debug by thinking Robert Charles Metzger

2. tools 
    http://ports.su/security

3. git 
  - 3 states
    - commited: 
      - data is safely stored in your local database
      - file in git directory
    - modified:
      - file changed but not commited to local database yet
      - working directory

    - staged: 
      - modified file are marked to go into next commit snapshot
      - staging area

    - flow

      working direcotry       add       staging area      commit      git directory

      modified files     ------------> snapshot of them ------------> permenently stored

    - 

  - git repository
    ```
    git init

    git clone
    ```

  - status
    ```
    git status 
    ```

  - usage
    - [remove large files committed](https://git-scm.com/docs/git-rm)
      - refferences
        https://git-scm.com/docs/git-rm
        http://blog.jessitron.com/2013/08/finding-and-removing-large-files-in-git.html
      ```
      # delete cached files
      git rm --cached /\*.exe
      
      find -type d -name bin | xargs git rm --cached  -r

      find -type d -name '*doc*' | xargs git rm --cached  -r --ignore-unmatch

      # This uses the -z argument to ls-files, and the -0 argument to xargs to cater safely/correctly for "nasty" characters in filenames.
      git ls-files -z --ignored --exclude-standard | xargs -0 git rm -r --cached

      # get deleted files log
        git log --diff-filter D --summary | grep  '^ delete'

        IFS=$'\n'
        del_names=`git log --all --pretty=format: --name-only --diff-filter=D | sort -u`

        for f in ${del_names}; do 
          echo git filter-branch --index-filter "git rm --cached --ignore-unmatch \"${f}\"" --prune-empty t -- --all
        done

        git filter-branch --index-filter 'git rm --cached --ignore-unmatch "work/4.doc"' --prune-empty t -- --all

        git filter-branch --index-filter 'git rm --cached --ignore-unmatch "system/c/docs/*.pdf" ' --force --prune-empty -- --all
      ```

    - ignore files and exclude some
      ```
      vim .gitignore
      */docs/*
      !*/docs/test/*
      ```

4. ocr tools for linux 
  - sites
    https://tools.ietf.org/inventory/author-tools.shtml
    http://imagemagick.org/script/download.php

    The act of extracting text from images is called OCR and Ubuntu has a wiki page dedicated to OCR. From that page:

    Available OCR tools,The Ubuntu Universe repositories contain the following OCR tools:
    ```
    gocr - A command line OCR
    fuzzyocr - spamassassin plugin to check image attachments
    libhocr0 - Hebrew OCR
    ocrad - Optical Character Recognition program
    ocrfeeder - Document layout analysis and optical character recognition system
    ocropus - document analysis and OCR system
    tesseract-ocr
    ```

    The Ubuntu multiverse respositories also contain:
    ```
    cuneiform - multi-language OCR system
    ```

5. regex
  - delete space between tow characters
    - groups: Regular expressions quick reference.pdf
      ```
      use                 | description
      ---                 | -----------
      (exp) Indexed       |  group
      (?<name>exp)        |  Named group
      (?<name1-name2>exp) |  Balancing group
      (?:exp)             |  Noncapturing group
      (?=exp)             |  Zero-width positive lookahead
      (?!exp)             |  Zero-width negative lookahead
      (?<=exp)            |  Zero-width positive lookbehind
      (?<!exp)            |  Zero-width negative lookbehind
      (?>exp)             |  Non-backtracking (greedy)
      ```

    - usage:
      - remove spaces
      ```
      (?<=[-\w])\s(?=\w)
      # orignal
      - C l e a r I c o n C a c h e   - R e m o v e B a s e S e t t i n g s   - B a s e S e t t i n g s   
      # after regex used
      -ClearIconCache   -RemoveBaseSettings   -BaseSettings
      # all 
      -ClearIconCache
      -RemoveBaseSettings
      -BaseSettings
      -UserIconConfigDelayed
      -UserIconConfig
      -UserConfig
      -ShowQLIcon
      -apply
      -reinstall
      -show
      -hide
      ie4uinit.exe -ClearIconCache
      taskkill /IM explorer.exe /F
      DEL "%localappdata%\IconCache.db" /A
      DEL "%localappdata%\Microsoft\Windows\Explorer\iconcache*" /A
      shutdown /r /f /t 00
      ```

      - add char between words
        - find with:
          ```
          ^(\w+\s)(.*)

          Aux Auxiliary Library
          Clfs Common Log File System
          Cc Cache Manager
          Cm Configuration Manager
          Ex Executive (Memory Allocation wrappers, etc)
          Flt Filter Manager
          Hal Hardware Abstraction Layer
          Io I/O Manager
          ```
        - replace with:
          ```
          $1 | $2

          Aux  | Auxiliary Library
          Clfs  | Common Log File System
          Cc  | Cache Manager
          Cm  | Configuration Manager
          Ex  | Executive (Memory Allocation wrappers, etc)
          Flt  | Filter Manager
          Hal  | Hardware Abstraction Layer
          Io  | I/O Manager
          ```

# ida 
  - change view
    spacebar

  - functions
    ```
    F A regular function. These are functions that IDA does not recognize as library functions.
    L A library function. IDA recognizes library functions through the use of signature-matching algorithms.
      If a signature does not exist for a given library function, the function will be labeled as a regular function instead.
    I An imported name, most commonly a function name imported from a shared library. The difference between this and a library
      function is that no code is present for an imported name, while the body of a library function will be present in the disassembly.
    C Named code. possible when IDA finds a name in a program’s symbol table but never sees a call to the corresponding
       program location.
    D Data. Named data locations typically represent global variables.
    A ASCII String data. This is a referenced data location containing a sequence of characters that conform to one of IDA’s 
      known string data types, such as a null-terminated ASCII C string
    ```
    The only stack variables that IDA will automatically generate names for are those that are directly referenced within a function.
    ```
    arg_xxxx : function args
    var_xxxx : local variables

    n : to rename a name
    ```

  - name
    ```
    sub_xxxxxx A subroutine at address xxxxxx
    loc_xxxxxx An instruction location at address xxxxxx
    byte_xxxxxx 8-bit data at location xxxxxx
    word_xxxxxx 16-bit data at location xxxxxx
    dword_xxxxxx 32-bit data at location xxxxxx
    unk_xxxxxx Data of unknown size at location xxxxxx
    ```

  - comment
    regular: ":"
    repeatable:  ';' 

- write hex data and disassmble
  ```
  # write to a file as raw data
  echo -n 'E80000000058050F000000FFE0E80000000058C3558BEC81EC5402000' | xxd -r -ps > code.bin
  # disasseble it
  ndisasm -b 32 code.bin > code.asm
  ```

# other
  # ROPC
    - BAP (Binary Analysis Platform)
    - stp(simple theorem prover) is a smp(satisfiability modulo theories) solvera

# code
  # when use '\' concaternate multiple lines no space after it
  # be extremely careful when using 3rd-party api, notice their every word
    ```
    PAGE_CODE();
    ```
  