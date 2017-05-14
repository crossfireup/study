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

    * view updates
      git add -u -n

    * undo add
      git reset <file>

    * add changes to stage
      git add . # add all incluing untraced files
      git commit -a -m "message"

    * stash
      git stash
      git stash list
      git stash apply stash@{1}  
      git stash pop # apply the top stash on the stack
      git stash drop <id>
      git stash clear

      git stash show -p stash@{0}
      git stash save --keep-index

    * add local repository to github
      * create a short name for use
        ```
        git remote add study https://github.com/HuangBR/study.git
        ```
      * push to remote 
        ```
        git push origin master
        ```
      * after all above, just use git push
        ```
        git push
        ```

    - add remote repository 
      - git remote
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
        https://help.github.com/articles/removing-sensitive-data-from-a-repository/
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
          echo git filter-branch --index-filter "git rm --cached --ignore-unmatch \"${f}\"" --prune-empty --force -- --all
        done

        git filter-branch --index-filter 'git rm --cached --ignore-unmatch "work/4.doc"' --prune-empty --force -- --all

        git filter-branch --index-filter 'git rm --cached --ignore-unmatch "system/c/docs/*.pdf" ' --force --prune-empty -- --all

        #  force-push your local changes to overwrite your GitHub repository
        git push --force --all

        # you can force all objects in your local repository to be dereferenced and garbage collected with the following commands 
        git for-each-ref --format='delete %(refname)' refs/original | git update-ref --stdin
        git reflog expire --expire=now --all
        git gc --prune=now
      ```

    - ignore files and exclude some
      ```
      vim .gitignore
      */docs/*
      !*/docs/test/*
      ```

    - push error
      ```
      vim .git/config
      url=https://github.com/xxx ---> url=ssh://git@github.com/xxx

      git remote set-url origin ssh://git@github.com/user/repo.git

      git config --global user.name xxxx
      git config --global user.email xxx
      git push origin master
      ```

    - submodules
      ```
      git submodule add <url>
      git diff --cached --submodule
      ```

    - merge two different repository
      - merge 2 local repos to one remote repository
      - submodule
      - subtree
      - merger -s subtree
      ```
      git remote tree merge      
      http://stackoverflow.com/questions/18858709/push-local-repo-to-new-sub-directory-of-remote-repo
      https://git-scm.com/book/en/v1/Git-Tools-Subtree-Mergin
      
      #push HookSSDT to wkd
      git config push.default upstream
      git push wkd master
      mkdir HookSSDT
      find . -maxdepth 1 -type f -print | grep -v "git" | xargs -I % git mv % HookSSDT
      git commit -m "new folder"
      git push wkd master

      # meget HookControl
      git remote add wkd https://github.com/HuangBR/wkd
      git fetch wkd master
      git merge --allow-unrelated-histories wkd/master -m "merge HookControl"
      mkdir HookControl
      find . -maxdepth 1 -type f -print | grep -v "git" | xargs -I % git mv % HookControl
      git commit -m "new folder"
      git push wkd master

      # get all
      git clone https://github.com/HuangBR/wkd
      cd wkd 

      # tips
      find . -name "*indexscreen_*" -a -type d -exec sh -c 'n={}; git mv {} ${n/indexscreen_/}' \;
      ```

    # amending a commit
      ```
      # Amending a Commit Without Changing Its Message
      git comit --amend --no-edit

      git commit --amend -m "Your new commit message"
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

- find
  ```
  -print0
              True; print the full file name a null character (instead of the newline character
              that -print uses).  This allows file names that contain
              newlines or other types of white space to be correctly
              interpreted by programs that process the find output.  This
              option corresponds to the -0 option of xargs.
  # handle whitespace
  find -type f -print0 | xargs -0 grep _NT_

  find -type f -exec echo '{}' +

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

# qemu
  - commands
    ```
    info pic 
    info registers
    ```
  
* vim 
  - configure
    ```vimrc
      windows :_vimrc
      set tabstop=4
      set nu
      set autoindent
      set shiftwidth=4
      set cindent
      set smartindent
      set expandtab
      syntax on

      # vim set backup and swp file position 
      # for windows
      :e $VIM/_vimrc
      " set nowrite
      " set nobackup
      " set noundofile
      set backupdir=~/.vim/backup/
      set directory=~/.vim/swap/
      set undodir=~/.vim/undo/


      set nocompatible
      filetype plugin indent on
      syntax on
      silent! runtime macros/matchit.vim
      set autochdir
      set backspace=indent,eol,start
      set foldenable
      set hidden
      set incsearch
      set laststatus=2
      set ruler
      set switchbuf=useopen,usetab
      set tags=./tags,tags;/
      set wildmenu
      nnoremap gb :buffers<CR>:sb<Space>


      highlight nonascii guibg=Red ctermbg=1 term=standout
      au BufReadPost * syntax match nonascii "[^\u0000-\u007F]"

    " VIM Configuration File
    " Description: Optimized for C/C++ development, but useful also for other things.
    " Author: Gerhard Gappmeier
    "

    " set UTF-8 encoding
    set enc=utf-8
    set fenc=utf-8
    set termencoding=utf-8
    " disable vi compatibility (emulation of old bugs)
    set nocompatible
    " use indentation of previous line
    set autoindent
    " use intelligent indentation for C
    set smartindent
    " configure tabwidth and insert spaces instead of tabs
    set tabstop=4        " tab width is 4 spaces
    set shiftwidth=4     " indent also with 4 spaces
    set expandtab        " expand tabs to spaces
    " wrap lines at 120 chars. 80 is somewaht antiquated with nowadays displays.
    set textwidth=120
    " turn syntax highlighting on
    set t_Co=256
    syntax on
    " colorscheme wombat256
    " turn line numbers on
    set number
    " highlight matching braces
    set showmatch
    " intelligent comments
    set comments=sl:/*,mb:\ *,elx:\ */

    " Install OmniCppComplete like described on http://vim.wikia.com/wiki/C++_code_completion
    " This offers intelligent C++ completion when typing ‘.’ ‘->’ or <C-o>
    " Load standard tag files
    set tags+=~/.vim/tags/cpp
    set tags+=~/.vim/tags/gl
    set tags+=~/.vim/tags/sdl
    set tags+=~/.vim/tags/qt4

    " Install DoxygenToolkit from http://www.vim.org/scripts/script.php?script_id=987
    let g:DoxygenToolkit_authorName="John Doe <john@doe.com>"

    " Enhanced keyboard mappings
    "
    " in normal mode F2 will save the file
    nmap <F2> :w<CR>
    " in insert mode F2 will exit insert, save, enters insert again
    imap <F2> <ESC>:w<CR>i
    " switch between header/source with F4
    map <F4> :e %:p:s,.h$,.X123X,:s,.cpp$,.h,:s,.X123X$,.cpp,<CR>
    " recreate tags file with F5
    map <F5> :!ctags -R –c++-kinds=+p –fields=+iaS –extra=+q .<CR>
    " create doxygen comment
    map <F6> :Dox<CR>
    " build using makeprg with <F7>
    map <F7> :make<CR>
    " build using makeprg with <S-F7>
    map <S-F7> :make clean all<CR>
    " goto definition with F12
    map <F12> <C-]>
    " in diff mode we use the spell check keys for merging
    if &diff
      ” diff settings
      map <M-Down> ]c
      map <M-Up> [c
      map <M-Left> do
      map <M-Right> dp
      map <F9> :new<CR>:read !svn diff<CR>:set syntax=diff buftype=nofile<CR>gg
    else
      " spell settings
      :setlocal spell spelllang=en
      " set the spellfile - folders must exist
      set spellfile=~/.vim/spellfile.add
      map <M-Down> ]s
      map <M-Up> [s
    endif
    ```

  - join two lines
      ```
      hostname: 
      output
      hostname2:
      output2

      :%v/:$/-1j
      hostname: output
      hostname2: output2

      :g/$/j
      :g/$/j3 # join every 3 lines

      1.start recording a macro 'q': qqJjq
      2.replay the macro 'q' 500 times: 500@q
      ```

  - write current content to disk
    ```
    :%!xxd

    da" Delete around quotes. Removes quoted text along with the quotes.
    ci( Change inside parentheses. Removes anything inside the parentheses, but leaves the parentheses there, while dropping you into insert mode.
    ```

  * case convert 
      ~    : Changes the case of current character

      guu  : Change current line from upper to lower.

      gUU  : Change current LINE from lower to upper.

      guw  : Change to end of current WORD from upper to lower.

      guaw : Change all of current WORD to lower.

      gUw  : Change to end of current WORD from lower to upper.

      gUaw : Change all of current WORD to upper.

      g~~  : Invert case to entire line

  * windows control
    ```
    # open multiple files with new tab
    vim -p f1 f2 f3
    #switch tab
    :tab f2 
    :p or :N  #previous
    :n  #next

    #new tab
    :tabn f3

    # close tab
    :tabc
    # move the current tab to the nth location with
    :ntabm 
    
    :sp filename for a horizontal split

    :vsp filename or :vs filename for a vertical split

    # start with own split
    vim -o files # open in herizon
    vim -O files # open in vector

    Ctrl+W, S (upper case) for horizontal splitting

    Ctrl+W, v (lower case) for vertical splitting

    Ctrl+W, Q to close one

    Ctrl+W, Ctrl+W to switch between windows

    Ctrl+W, J (xor K, H, L) to switch to adjacent window (intuitively up, down, left, right)

    Ctrl-W c to close the current window
    Ctrl-W o to close all windows except the current one.

    Ctrl-W t # top window
    Ctrl-W b # bottom window

    # switch between buffers
    :bf            # Go to first file.
    :bl            # Go to last file
    :bn            # Go to next file.
    :bp            # Go to previous file.
    :bw            # Close file.
    ```
  
  * paste from outside
    ```
      Do this before:

      :set paste

      Then after:

      :set nopaste
    ```
      set pastetoggle=<F2>

      in normal and visual modes, "xp pastes the contents of the register x.

      This works with special registers as well: "+p (or "*p) pastes the contents of the clipboard,
        "/p pastes the last search, and ":p pastes the last command. 
      For example, you might want to save a complex search and replace (:%s///g) that you have just used, which you can do by pasting with ":p. 

  * paste to/from clipboard
    ```
    +y

    +p

    copy to system clipboard
    gg
    :%y+

    g g " + y G 

    ggVG
    ```

  * save files as sudo
    ```
    :w !sudo dd of=%

    Making this trick easy

    You can add this to your .vimrc to make this trick easy-to-use: just type :w!!.

    " Allow saving of files as sudo when I forgot to start vim using sudo.
    cmap w!! w !sudo tee > /dev/null %

    The > /dev/null part explicitly throws away the standard output, since, as I said, we don't need to pass anything to another piped command.
    ```

  * comment/uncomment

    * press Esc (to leave editing or other mode)
    * hit ctrl+v (visual block mode)
    * use the up/down arrow keys to select lines you want (it won't highlight everything - it's OK!)
    * Shift+i (capital I)
    * insert the text you want, i.e. '% '
    * press Esc

  * swap char/line
    1. Swap the current character (the character under the cursor) with the next:

          xp

    2. Swap the current character with the previous:

          Xp

    3. Swap the current line with the next (but see below for a better method):

          ddp

          ddP

    4. swap words
          dwwp
          dwbP
  
  * format code

      gg=G

      Explanation:
        gg goes to the top of the file, 
        = is a command to fix the indentation
        G tells it to perform the operation to the end of the file.
      
      :!indent %
  
  * highlight

      To turn off highlighting until the next search:

      :nohl

      Or turn off highlighting completely:

      set nohlsearch

      Or, to toggle it:

      set hlsearch!

      nnoremap <F3> :set hlsearch!<CR>

    * delete
      
      d63G # delete from cursor to line 63
      
      :a,bd # delete from a to b
      
      :,bd # delete from current to d 

      :g/^/+d # delete every other line
    
    * tab pages
      gt
      gT

    * map
      n  Normal mode map. Defined using ':nmap' or ':nnoremap'.
      i  Insert mode map. Defined using ':imap' or ':inoremap'.
      v  Visual and select mode map. Defined using ':vmap' or ':vnoremap'.
      x  Visual mode map. Defined using ':xmap' or ':xnoremap'.
      s  Select mode map. Defined using ':smap' or ':snoremap'.
      c  Command-line mode map. Defined using ':cmap' or ':cnoremap'.
      o  Operator pending mode map. Defined using ':omap' or ':onoremap'.
      
      <Space>  Normal, Visual and operator pending mode map. Defined using
                ':map' or ':noremap'.
      !  Insert and command-line mode map. Defined using 'map!' or
          'noremap!'.
    * show tab whitespace
      ```
      :set listchars=eol:$,tab:>-,trail:~,extends:>,precedes:<
      :set list

      autocmd FileType make set noexpandtab shiftwidth=8 softtabstop=0

      cat -vE file # -v show-nonprinting -E show-end -e=-vE

      highlight nonascii guibg=Red ctermbg=1 term=standout
      au BufReadPost * syntax match nonascii "[^\u0000-\u007F]"
      ```
    * file name  
      ```
      :echo @% 	def/my.txt 	directory/name of file (relative to the current working directory of /abc)
      :echo expand('%:t') 	my.txt 	name of file ('tail')
      :echo expand('%:p') 	/abc/def/my.txt 	full path
      :echo expand('%:p:h') 	/abc/def 	directory containing file ('head')
      :echo expand('%:p:h:t') 	def 	First get the full path with :p (/abc/def/my.txt), then get the head of that with :h (/abc/def), then get the tail of that with :t (def)
      :echo expand('%:r') 	my 	name of file less one extension ('root')
      :echo expand('%:e') 	txt 	name of file's extension ('extension') 
      ```

    * mark
      ```
      ma 	set mark a at current cursor location
      'a 	jump to line of mark a (first non-blank character in line)
      `a 	jump to position (line and column) of mark a
      d'a 	delete from current line to line of mark a
      d`a 	delete from current cursor position to position of mark a
      c'a 	change text from current line to line of mark a
      y`a 	yank text to unnamed buffer from cursor to position of mark a
      :marks 	list all the current marks
      :marks aB 	list marks a, B
      ```
    
    * reverse lines
      ```
      help 12.4
      1. set a marker at the last line you want reverse (I name the marker 'a' using ma), 
      2. move cursor to the first line of the block, 
      3. type :'a,.g/^/m 'a

      For those more comfortable with Visual mode:
      1. Identify the line number above the selection you want flipped using :set nu.
      2. Shift-V to highlight selection you want flipped (visual mode).
      3. :g/^/m <Line number from step 1>.
      ```

    * replace words
      :%s/a/b/g
      :3,9s/a/b/g # 3-9 line

    - registers
      ```
      There are nine types of registers:			*registers* *E354*
      1. The unnamed register ""
      2. 10 numbered registers "0 to "9
      3. The small delete register "-
      4. 26 named registers "a to "z or "A to "Z
      5. four read-only registers ":, "., "% and "#
      6. the expression register "=
      7. The selection and drop registers "*, "+ and "~ 
      8. The black hole register "_
      9. Last search pattern register "/

      ["x]yy			Yank [count] lines [into register x] |linewise|.
      							*Y*
      ["x]Y			yank [count] lines [into register x] (synonym for	yy, 

      # delete the black hole register 
      "_d
      "_x
      ```

    - syntax
      ```
      ctrl N

      filetype plugin on
      au FileType php setl ofu=phpcomplete#CompletePHP
      au FileType ruby,eruby setl ofu=rubycomplete#Complete
      au FileType html,xhtml setl ofu=htmlcomplete#CompleteTags
      au FileType c setl ofu=ccomplete#CompleteCpp
      au FileType css setl ofu=csscomplete#CompleteCSS
      ```

    - plugin
      [YouCompleteMe](https://github.com/Valloric/YouCompleteMe)
      [vundle](https://github.com/VundleVim/Vundle.vim#about)
      ```
      git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim

      # vim /etc/vim/vimrc
      set nocompatible              " be iMproved, required
      filetype off                  " required

      set rtp+=~/.vim/bundle/Vundle.vim
      call vundle#begin()

      " let Vundle manage Vundle, required
      Plugin 'VundleVim/Vundle.vim'

      Plugin 'https://github.com/Valloric/YouCompleteMe.git'

      call vundle#end()            " required
      filetype plugin indent on    " required

      # install tools
      sudo apt-get install build-essential cmake
      sudo apt-get install python-dev python3-dev

      # Compiling YCM with semantic support for C-family languages:
      cd ~/.vim/bundle/YouCompleteMe
      ./install.py --clang-completer
      ```

# tmux

  Prefix-Command,tmux default CTRL+b。
  * session:
    ```
    create: tmux new-session -s <session-name> or tmux new -s <session-name>
    detach: prefix d
    attach: tmux attach -t <session-name> or tmux a -t <session-name>
    tmux ls: list sessions
    prefix $: rename sessions

    tmux -S /tmp/tmux/msf4 attach
    ```

  * window
    ```
    tmux new -n <window-name>
    new window: prefix c
    previous: prefix p
    next: prefix n
    switch to previous active windows: prefix space
    window number: prefix <win-num>
    list: prefix w
    close: prefix &
    rename: prefix ,
    ```

  * panel
    ```
    list panel nmuber: prefix q
    vsplit: prefix %
    hsplit: prefix "
    switch: prefix o
    array : prefix <left/rigth arrow>
    layout: prefix space 
    exit:   prefix D
    close:  prefix x
    ```text
    水平平分（even-horizontal）
    垂直平分（even-vertical）
    主窗格最大化，其他窗格水平平分（main-horizontal）
    主窗格最大化，其他窗格垂直平分（main-vertical）
    平铺，窗格均等分（tiled）
    ```
    ```

  * [more usage](https://mutelight.org/practical-tmux)
    ```
    scroll
    set -g mouse on

    (tmux version 2.1 and up) or

    set -g mode-mouse on

    tmux kill-server && tmux

    # copy and paste using putty
    tmux config: setw -g mode-mouse on

    # copy from tmux to system clipboard:
      SHIFT select the text by mouse, then click left-button of mouse.

    # paste some text into tmux:
      press SHIFT and click right-button of mouse.
    ```

# visual studio
  - resource file
    ```
    # add to rc file
    #include <winres.h>
    #pragma code_page(1252)

     "C:\Program Files (x86)\Windows Kits\8.1\bin\x86\rc.exe" /D _UNICODE /D UNICODE /l"0x0409" /nologo /fo"Debug\ExplorePE.res" ExplorePE.rc
     ```

# tips
  - always pay attention to the version of the software you install, or it may be a disaster
    - VS2015 and VS2013, and their related QT version
      - _NT_TARGET_VERSION not set
        ```xml
        <!-- WindowsDriver.Shared.Props -->
        <When Condition="('$(TargetVersion)'=='Windows7') Or ('$(TargetVersion)'=='Win7')">
          <PropertyGroup>
            <_NT_TARGET_VERSION>$(_NT_TARGET_VERSION_WIN7)</_NT_TARGET_VERSION>
            <CURRENT_NTDDI_VERSION>0x06010000</CURRENT_NTDDI_VERSION>
            <CURRENT_WIN32_WINNT_VERSION>0x0601</CURRENT_WIN32_WINNT_VERSION>
            <SUBSYSTEM_VERSION_LATEST>6.01</SUBSYSTEM_VERSION_LATEST>
            <!-- Continue to default to Vista due to extra requirement to link to ole32.dll in Win7 stubs -->
            <MIDL_TARGET Condition="'$(MIDL_TARGET)' == ''">$(MIDL_TARGET_VISTA)</MIDL_TARGET>
            <DDKSpec>win7</DDKSpec>
            <Inf2CatWindowsVersionList>7_$(DDKPlatform)</Inf2CatWindowsVersionList>
          </PropertyGroup>
        </When>
      ```
      - symbols not found
      - exit unexpected

  - start debug with error in vs
    *.vcxproj.user has user-defined variables that can be used to build the project, usually the git ignore this file for that its was set as a system varaible and different between machines
    ```
    <?xml version="1.0" encoding="utf-8"?>
    <Project ToolsVersion="14.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
      <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
      <QTDIR>C:\Qt\Qt5.8.0_vs2013\5.8\msvc2013</QTDIR>
        <LocalDebuggerEnvironment>PATH=$(QTDIR)\bin%3b$(PATH)</LocalDebuggerEnvironment>
      </PropertyGroup>
      <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
      <QTDIR>C:\Qt\Qt5.8.0_vs2013\5.8\msvc2013</QTDIR>
        <LocalDebuggerEnvironment>PATH=$(QTDIR)\bin%3b$(PATH)</LocalDebuggerEnvironment>
      </PropertyGroup>
    </Project>
    ```
    http://blogs.microsoft.co.il/sasha/2007/08/11/debugging-and-investigation-tools/

  - vs offline
    - configure and run
      ```
      vs_community__797361372.1493258229.exe --layout D:\Software\programming\vs2017offline --lang zh-CN en-US
      ```

  - bash on windows
    ```
    lxrun /setdefaultuser root /y
    ```

  - htop
    ```
    nice [ - ] +
    k kill
    p m t : sort by processor usage, memory, time
    s : strace
    l : losf
    L : lib usage
    ```

* autotools
    * autoconf automake
                   autoconf
      configure.ac ---------> configure 
            |
            |       automake
      Makefile.am -----------> Makefile.in

      Standard ‘configure.ac’ Layout:
        Autoconf requirements
        AC_INIT(package, version, bug-report-address)
        information on the package
        checks for programs
        checks for libraries
        checks for header fles
        checks for types
        checks for structures
        checks for compiler characteristics
        checks for library functions
        checks for system services
        AC_CONFIG_FILES([file...])
        AC_OUTPUT
                                  rename
      autoscan --> configure.scan --------> configure.ac

      

      - autoconf: create configure from configure.ac
      
      - autoheader: create config.h.in from configure.ac

      - autoreconf: update configure file, run all tools in the right order
      
      - autoscan: scan sources for common portability problems and related macros missing from configure.ac

      - autoupdate: update obsolete macros in configure.ac

      - ifnames: Gather identifiers from all #if/#ifdef/... directives

      - autom4te: the heart of autoconf, drives M4 and implements the features used by most of the above tools. Useful for creating more than just configure files
      
      - automake: create Makefile.ins from configure.acs and configure.ams

      - aclocal: Scan configure.ac for uses of third-party macros and gather definitions in aclocal.m4.


        - auxiliary tools used during build
          - depcomp
          - install-sh
          - missing

       

    * automake
      AM_CFLAGS

    - libtool
      - why 
        - encourage modularity and reuse of code (both conceptually and physically) in GNU programs.
        - the absence of a standard procedure for creating shared libraries on diﬀerent platforms. 
      - aim
        - elagant
        - integrate with automake and autoconf
        - portability to other (non-GNU) architectures and tools is desirable

      - solve problem
        - control what sort of libraries are built
        - can be tricky to run dynamically linked programs whose libraries have not yet been installed
          ```
          LD_LIBRARY_PATH
          LD_RUN_PATH
          ```
        - operate consistently even on hosts that don’t support shared libraries.
        - build shared libraries may diﬀer wildly from host to host.
        - not always obvious with what prefx or sufx a shared library should be installed
        - needs a simple library version number abstraction, so that shared libraries can be upgraded in place
        - The install Makefile target should warn the package installer to set the proper environment variables (LD_LIBRARY_PATH or equivalent), or run ldconfig.

      ```
      LT_INIT

    - usage
      - autoscan 

      - makefile
        ```
        AC_SUBST(variable, [value])
    
# todo
- how default icon being loaded in QT
  - a rc file being compile by rc.exe and link with the res file
  - not find function call setWindowIcon