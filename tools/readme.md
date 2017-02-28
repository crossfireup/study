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
