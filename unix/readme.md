# start
  https://www.linux.com/learn/kernel-newbie-corner-kernel-and-module-debugging-gdb
  http://www.makelinux.net/ldd3/
  https://communities.vmware.com/
  http://sysprogs.com/VisualKernel/tutorials/vmware/  

* umask
	
    * For directories, the base permissions are (rwxrwxrwx) 0777 
	* for files they are 0666 (rw-rw-rw).
	```bash
    # set umask to 077:
	umask u=rwx,g=,o=
    ```

* strace
	strace -ff -e trace=file -o /tmp/trace /etc/init.d/mysqld start 

* iptables
	 
    /sbin/service iptables save

	This executes the iptables init script, which runs the /sbin/iptables-save program and writes the current iptables configuration to /etc/sysconfig/iptables. The existing /etc/sysconfig/iptables file is saved as /etc/sysconfig/iptables.save.

	The next time the system boots, the iptables init script reapplies the rules saved in /etc/sysconfig/iptables by using the /sbin/iptables-restore command.

	While it is always a good idea to test a new iptables rule before committing it to the /etc/sysconfig/iptables file, it is possible to copy iptables rules into this file from another system's version of this file. This provides a quick way to distribute sets of iptables rules to multiple machines. 
    ```shell
    iptables -t nat -I PREROUTING -t tcp --dport 8888 -j REDIRECT --to 80
    iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 80 \
       -j REDIRECT --to-ports 8080 
    ```

  ## redirect port 5001 to port 110 (POP3) at 123.123.123.123:
    ```bash
    iptables -t nat -A PREROUTING -p tcp --dport 5001 \
    -j DNAT --to-destination 123.123.123.123:110
    ```   
  ## Change sender to redirecting machine:m
    ```bash
    iptables -t nat -A POSTROUTING -p tcp --dport 110 \
       -j MASQUERADE
    ```
  ## netfilter Read more at: http://scl.io/98OfGfTx#gs.gx4n9uY
  
    * tables:
      name   | chains
      ----   | -- 
      FILTER |Input, Output, Forward
      NAT    |Prerouting, Postrouting, Output
      MANGLE | Prerouting, Postrouting, Input, Output, Forward 

    * chains:
      name        | description
      ------------| -----------
      PREROUTING  | Immediately after being received by an interface.
      POSTROUTING | Right before leaving an interface.
      INPUT       | Right before being handed to a local process.
      OUTPUT      | Right after being created by a local process.
      FORWARD     | For any packets coming in one interface and leaving out another.

    * [netfilter](http://www.netfilter.org/documentation/HOWTO/netfilter-hacking-HOWTO-3.html)
    ```
            --->PRE------>[ROUTE]--->FWD---------->POST------>
            Conntrack    |       Mangle   ^    Mangle
            Mangle       |       Filter   |    NAT (Src)
            NAT (Dst)    |                |    Conntrack
            (QDisc)      |             [ROUTE]
                        v                |
                        IN Filter       OUT Conntrack
                        |  Conntrack     ^  Mangle
                        |  Mangle        |  NAT (Dst)
                        v                |  Filter
    ```
* bash shortcut
  * Moving the cursor:

    Ctrl + a   Go to the beginning of the line (Home)
    Ctrl + e   Go to the End of the line (End)
    Ctrl + p   Previous command (Up arrow)
    Ctrl + n   Next command (Down arrow)
    Alt + b   Back (left) one word
    Alt + f   Forward (right) one word
    Ctrl + f   Forward one character
    Ctrl + b   Backward one character
    Ctrl + xx  Toggle between the start of line and current cursor position

  * Editing:

  Ctrl + L   Clear the Screen, similar to the clear command

    Alt + Del Delete the Word before the cursor.
    Alt + d   Delete the Word after the cursor.
  Ctrl + d   Delete character under the cursor
  Ctrl + h   Delete character before the cursor (Backspace)

  Ctrl + w   Cut the Word before the cursor to the clipboard.
  Ctrl + k   Cut the Line after the cursor to the clipboard.
  Ctrl + u   Cut/delete the Line before the cursor to the clipboard.

    Alt + t   Swap current word with previous
  Ctrl + t   Swap the last two characters before the cursor (typo).
  Esc  + t   Swap the last two words before the cursor.

  ctrl + y   Paste the last thing to be cut (yank)
    Alt + u   UPPER capitalize every character from the cursor to the end of the current word.
    Alt + l   Lower the case of every character from the cursor to the end of the current word.
    Alt + c   Capitalize the character under the cursor and move to the end of the word.
    Alt + r   Cancel the changes and put back the line as it was in the history (revert).
  ctrl + _   Undo
  
  * TAB        Tab completion for file/directory names

      For example, to move to a directory 'sample1'; Type cd sam ; then press TAB and ENTER.
      type just enough characters to uniquely identify the directory you wish to open.

  * Special keys: Tab, Backspace, Enter, Esc

      Text Terminals send characters (bytes), not key strokes.
      Special keys such as Tab, Backspace, Enter and Esc are encoded as control characters.
      Control characters are not printable, they display in the terminal as ^ and are intended to have an effect on applications.

      Ctrl+I = Tab
      Ctrl+J = Newline
      Ctrl+M = Enter
      Ctrl+[ = Escape

      Many terminals will also send control characters for keys in the digit row:
      Ctrl+2 → ^@
      Ctrl+3 → ^[ Escape
      Ctrl+4 → ^\
      Ctrl+5 → ^]
      Ctrl+6 → ^^
      Ctrl+7 → ^_ Undo
      Ctrl+8 → ^? Backward-delete-char

      Ctrl+v tells the terminal to not interpret the following character, so Ctrl+v Ctrl-I will display a tab character,
      similarly Ctrl+v ENTER will display the escape sequence for the Enter key: ^M

  * History:

    Ctrl + r   Recall the last command including the specified character(s)
              searches the command history as you type.
              Equivalent to : vim ~/.bash_history. 
    Ctrl + p   Previous command in history (i.e. walk back through the command history)
    Ctrl + n   Next command in history (i.e. walk forward through the command history)

    Ctrl + s   Go back to the next most recent command.
              (beware to not execute it from a terminal because this will also launch its XOFF).
    Ctrl + o   Execute the command found via Ctrl+r or Ctrl+s
    Ctrl + g   Escape from history searching mode
          !!   Repeat last command
        !abc   Run last command starting with abc
      !abc:p   Print last command starting with abc
          !$   Last argument of previous command
    ALT + .   Last argument of previous command
          !*   All arguments of previous command
    ^abc­^­def   Run previous command, replacing abc with def

  * Process control:

  Ctrl + C   Interrupt/Kill whatever you are running (SIGINT)
  Ctrl + l   Clear the screen
  Ctrl + s   Stop output to the screen (for long running verbose commands)
              Then use PgUp/PgDn for navigation
  Ctrl + q   Allow output to the screen (if previously stopped using command above)
  Ctrl + D   Send an EOF marker, unless disabled by an option, this will close the current shell (EXIT)
  Ctrl + Z   Send the signal SIGTSTP to the current task, which suspends it.
              To return to it later enter fg 'process name' (foreground).

  * Emacs mode vs Vi Mode

      All the above assume that bash is running in the default Emacs setting, if you prefer this can be switched to Vi shortcuts instead.

      Set Vi Mode in bash:

      $ set -o vi 

      Set Emacs Mode in bash:

      $ set -o emacs 



* vim 

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

        :sp filename for a horizontal split

        :vsp filename or :vs filename for a vertical split

        Ctrl+W, S (upper case) for horizontal splitting

        Ctrl+W, v (lower case) for vertical splitting

        Ctrl+W, Q to close one

        Ctrl+W, Ctrl+W to switch between windows

        Ctrl+W, J (xor K, H, L) to switch to adjacent window (intuitively up, down, left, right)

    * configure
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

        +y

        +p

        copy to system clipboard
        gg
        :%y+

        g g " + y G 

        ggVG

    * save files as sudo

        :w !sudo dd of=%

        Making this trick easy

        You can add this to your .vimrc to make this trick easy-to-use: just type :w!!.

        " Allow saving of files as sudo when I forgot to start vim using sudo.
        cmap w!! w !sudo tee > /dev/null %

        The > /dev/null part explicitly throws away the standard output, since, as I said, we don't need to pass anything to another piped command.

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
        :set listchars=eol:$,tab:>-,trail:~,extends:>,precedes:<
        :set list

        autocmd FileType make set noexpandtab shiftwidth=8 softtabstop=0

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



* linux
  * runlevel

    0: halt
    1: single-user
    2: multi-user
    3: multi-user with networking
    4: undefined (user defined)
    5: multi-user with display manager (graphical login)
    6: reboot

  *  Name Service Switch (NSS). 

  * [systemd](https://www.freedesktop.org/wiki/Software/systemd/)
    
    Unit:

    Service

    Install

  * [dns](https://wiki.debian.org/NetworkConfiguration)

    1. The resolvconf program
    2. The network-manager daemon
    3. DHCP clients 

    * The resolv.conf file typically contains the IP addresses of nameservers (DNS name resolvers) that will attempt to translate names into addresses for any node available on the network. There will be a line or lines that look like this:
      ```
      nameserver 12.34.56.78
      nameserver 12.34.56.79
      ```
    * When resolvconf is properly installed, the resolv.conf configuration file at /etc/resolv.conf is replaced by a symbolic link to   /etc/resolvconf/run/resolv.conf and the resolver instead uses the configuration file that is dynamically generated by resolvconf at /etc/resolvconf/run/resolv.conf. 

    * If the resolvconf program is installed, you should not edit the resolv.conf configuration file manually as it will be dynamically changed by programs in the system. If you need to manually define the nameservers (as with a static interface), add a line something like the following to the interfaces configuration file at /etc/network/interfaces: 
      ```
      dns-nameservers 12.34.56.78 12.34.56.79
      ```

  * DHCP Client Configuration

    Example: dhclient3 uses /etc/dhcp/dhclient.conf. The setting you want is

    supersede domain-name-servers 12.34.56.78, 12.34.56.79;

    or perhaps

    prepend domain-name-servers 12.34.56.78, 12.34.56.79;

  * wiresharek
    bootp:
      bootp.dhcp 
    udp.port==67
    eth.addr == ff:ff:ff:ff:ff:ff



# ubuntu 16.10 #
  * ppa
    
    personal package archive

    chfn ............... change your "Real Name" as seen on finger
    
    chsh ............... change the shell you log into

    [keystone install](http://docs.openstack.org/liberty/install-guide-ubuntu/keystone-install.html)


* signal
    * Typing Ctrl + C normally causes the shell to send SIGINT to your program
        Ctrl + \ SIGQUIT
    ```bash
    kill -l
    kill -USR1 pid
    kill -USR2 pid
    kill -9 pid
    ```
    * SIGCLD System V:
        not produce zombies process if ignored

    * SIGCHLD bsd,posix.1 adopt bsd: 
        if ingnored produce zombies in bsd, wait child will emit zombies

        A state change is considered to be: the child terminated; the child 
        was stopped by a signal; or the child was resumed by a signal. 
        In the case of a terminated child, performing a wait allows the system 
        to release the resources associated with the child; if a wait is not 
        performed, then the terminated child remains in a "zombie" state (see NOTES below).

        A child that terminates, but has not been waited for becomes a
       "zombie".  The kernel maintains a minimal set of information about
       the zombie process (PID, termination status, resource usage
       information) in order to allow the parent to later perform a wait to
       obtain information about the child.  As long as a zombie is not
       removed from the system via a wait, it will consume a slot in the
       kernel process table, and if this table fills, it will not be
       possible to create further processes.  If a parent process
       terminates, then its "zombie" children (if any) are adopted by
       init(1), which automatically performs a wait to remove the zombies.

* core dump
    ```bash
    sysctl kernel.core_pattern
    # kernel.core_pattern = |/usr/libexec/abrt-hook-ccpp %s %c %p %u %g %t e
    sysctl -p
    ulimit -c unlimited
    ulimit -c 
    ```
  * gdb:
    * compile

        gcc -g -O0 

    * gdb exec_file core_file

        info variable

        info locals

        p <variable name>

        i register (i r)

        info proc map

        disassamble

        ctrl + x + a

     * multiple process:
          set follow-fork-mode child/parent
          set detach-on fork off

     * watch: (same for break print)
      ```
        watch foo
        watch -l foo
        rwatch foo         # stop if foo is read
        watch foo thread 3 # watch if thread 3 modify foo
        watch foo if foo = 3 
      ```

      * thread
      ```
        thread apply 1-4 backtrace/print $sp
        thread apply all backtrace full
      ```
      
      * dynamic printf
        dprintf mutex_lock, ...
        set dprintf-style gdb/call
        set dprintf-channel mylog
        set dprintf-function fprintf

      * catch
        catch syscall nanosleep
        catch syscall 100

        tbreak # temparory break
        rbreak # regex break
        command
        silent # suppress output on breakpoint hit
        info line * $pc
        info line foo.c:42
    D_PRELOAD to the path of a shared object, that file will be loaded before any other library (including the C runtime, libc.so).

    * common commands
      command | description
      --| --
      h[elp] 	     |     Get help on gdb commands
      h[elp]       |     $ <$ cmd$ >$ 	Get help on a specific gdb command
      r[un] 	     |     Run to next breakpoint or to end
      s[tep] 	     |     Single-step, descending into functions
      [ext]        |    	Single-step without descending into functions
      fin[ish] 	   |     Finish current function, loop, etc. (useful!)
      c[ontinue] 	 |     Continue to next breakpoint or end
      up 	         |     Go up one context level on stack (to caller)
      do[wn] 	     |     Go down one level (only possible after up)
      l[ist] 	     |      Show lines of code surrounding the current point
      p[rint] $ <$ name$ >$ |	Print value of variable called $ <$ name$ >$
      p $ \ast<$ name$ >$   |	  Print what is pointed to by $ <$ name$ >$
      p/x $ <$ name$ >$ 	  |  Print value of $ <$ name$ >$ in hex format
      p $ <$ name$ >$ @$ <$ n$ >$ |	print $ <$ n$ >$ values starting at $ <$ name$ >$
      p $ <$ chars$ >$ $ <$ tab$ >$ |	List all variables starting with $ <$ chars$ >$
      b[reak] $ <$ name$ >$ |	Set a breakpoint at function $ <$ name$ >$
      b $ <$ class$ >$ ::$ <$ name$ >$ |	Set a breakpoint at $ <$ name$ >$ in $ <$ class$ >$
      b $ <$ class$ >$ ::$ <$ tab$ >$ |	List all members in $ <$ class$ >$
      h[elp] b |	Documentation for setting breakpoints
      i[nfo] b |	List breakpoints
      i 	| List all info commands
      dis[able] 1 |	Disable breakpoint 1
      en[able] 1  |	Enable breakpoint 1
      d[elete] 1 	| Delete breakpoint 1
      d 1 2       |	Delete breakpoints 1 and 2
      d 	        | Delete all breakpoints
      cond[ition] 1 $ <$ expr$ >$ |	Stop at breakpoint 1 only if $ <$ expr$ >$ is true
      cond 1 |	Make breakpoint 1 unconditional
      comm[ands] 1 	| Add a list of gdb commands to execute each time breakpoint 1 is hit
        (usually just print <var>)

    * debug
      print x=4 # set and print x
      set {int}0x83040 = 4 # set memory in 0x8304
      whatis $ebp
        void *
      
      jump *0x1000

      break *0x7c00 if 

      save breakpoints brks.gdb
      source -s brks.gdb   # If -s is specified, then gdb searches for filename on the search path even if filename specifies a directory
      


# file system #
    
  * ZFS has three major design goals: https://www.freebsd.org/doc/en_US.ISO8859-1/books/handbook/zfs.html

    1. __Data integrity__: All data includes a checksum of the data. When data is written, the checksum is calculated and written along with it. When that data is later read back, the checksum is calculated again. If the checksums do not match, a data error has been detected. ZFS will attempt to automatically correct errors when data redundancy is available.

    2. __Pooled storage__: physical storage devices are added to a pool, and storage space is allocated from that shared pool. Space is available to all file systems, and can be increased by adding new storage devices to the pool.

    3. __Performance__: multiple caching mechanisms provide increased performance. ARC is an advanced memory-based read cache. A second level of disk-based read cache can be added with L2ARC, and disk-based synchronous write cache is available with ZIL.


# network #
 * ppp
    CHAP versus PAP:
    
    With PPP, each system may require its peer to authenticate itself using one of two authentication protocols. These are the Password Authentication Protocol (PAP), and the Challenge Handshake Authentication Protocol (CHAP). When a connection is established, each end can request the other to authenticate itself, regardless of whether it is the caller or the callee. Below I will loosely talk of `client' and `server' when I want to distinguish between the authenticating system and the authenticator. A PPP daemon can ask its peer for authentication by sending yet another LCP configuration request identifying the desired authentication protocol. 

    PAP works basically the same way as the normal login procedure. The client authenticates itself by sending a user name and an (optionally encrypted) password to the server, which the server compares to its secrets database. This technique is vulnerable to eavesdroppers who may try to obtain the password by listening in on the serial line, and to repeated trial and error attacks.

    CHAP does not have these deficiencies. With CHAP, the authenticator (i.e. the server) sends a randomly generated ``challenge'' string to the client, along with its hostname. The client uses the hostname to look up the appropriate secret, combines it with the challenge, and encrypts the string using a one-way hashing function. The result is returned to the server along with the client's hostname. The server now performs the same computation, and acknowledges the client if it arrives at the same result.

    CHAP is doesn't only authenticate client at startup time, but sends challenges at regular intervals to make sure the client hasn't been replaced by an intruder, for instance by just switching phone lines. 

    pppd keeps the secret keys for CHAP and PAP in two separate files, called /etc/ppp/chap-secrets and pap-secrets, respectively

    As CHAP is so much stronger than PAP, pppd tries to use the former whenever possible. If the peer does not support it, or if pppd can't find a CHAP secret for the remote system in its chap-secrets file, it reverts to PAP. If it doesn't have a PAP secret for its peer either, it will refuse to authenticate altogether. As a consequence, the connection is closed down. 

# bash #

  * ls  directories in current
    ```bash
    ls -d */  # list only subdirectories in the current one
    ls -F | grep --color /
    :(){ : &};:
    ```

  * kill a group process
    ```bash
    pids=` ps x -o  "%p %r %c" | grep bash | sort -k 2 | awk '{print $2}' | sort -u `
    for pid in ${pids};do kill -TERM -- -$pid ;done;

    ps -p 6514 -F
    ```

  * redirect
    
    write stdout and stderr to logfie and stderr to stdout:
    /a.out < /etc/services 2>&1 >>stderr.out | tee --append stderr.out
    

  * [anonymize ssh traffic](http://tor.stackexchange.com/questions/123/how-can-i-anonymize-my-ssh-traffic-using-the-tor-network/127#127)

    1. For SSH you can do something like the following:
    ```
    ssh -o ProxyCommand='nc -x localhost:$orport %h %p' example.com
    ```

    2. Options can also be configured in your ~/.ssh/config (or /etc/ssh/ssh_config, or the equivalent on your OS) file:
    ```
    Host example
        Hostname example.com
        ProxyCommand /usr/bin/nc -x localhost:$orport %h %p
    ```

    3. Rsync can then use ssh as its remote shell and it will pick up the previous config:
      ```
      rsync -e ssh example:path/to/files /dest
      ```
      > or, by directly passing arguments to the remote shell:
      
      ```
      rsync -e "ssh -o ProxyCommand='nc -x localhost:$orport %h %p'" example.com /dest
      ```

    4. Finally, you can use the RSYNC_CONNECT_PROG environment variable to set up all future RSYNC invocations to use Tor (without having to manually specify it each time):
        ```
        export RSYNC_CONNECT_PROG='ssh proxyhost nc -x localhost:$orport %h %p'
        rsync example.com:/src /dest 
        ```
       Replace $orport with the port you've got Tor's SOCKS proxy listening on.

# tmux

  Prefix-Command,tmux default CTRL+b。
  * session:

    create: tmux new-session -s <session-name> or tmux new -s <session-name>
    detach: prefix d
    attach: tmux attach -t <session-name> or tmux a -t <session-name>
    tmux ls: list sessions
    prefix $: rename sessions

  *window

    tmux new -n <window-name>
    new window: prefix c
    previous: prefix p
    next: prefix n
    switch to previous active windows: prefix space
    window number: prefix <win-num>
    list: prefix w
    close: prefix &
    rename: prefix ,

  * panel

    list panel nmuber: prefix q
    vsplit）：prefix %
    hsplit：prefix "
    switch: prefix o
    array : prefix <left/rigth arrow>
    layout: prefix space 
    ```text
    水平平分（even-horizontal）
    垂直平分（even-vertical）
    主窗格最大化，其他窗格水平平分（main-horizontal）
    主窗格最大化，其他窗格垂直平分（main-vertical）
    平铺，窗格均等分（tiled）
    ```

# nginx
--------------------------
  * master: 
    * reading and validating configuration
    * creating, binding and closing sockets
    * starting, terminating and maintaining the configured number of worker processes
    * reconfiguring without service interruption
    * controlling non-stop binary upgrades (starting new binary and rolling back if necessary)
    * re-opening log files
    * compiling embedded Perl scriptss
  * worker:
     * accept, handle and process connections from clients
     * provide reverse proxying 
     * filtering functionality
     * etc
  * cache loader process
    * repares nginx instances to work with files already stored on disk in a specially allocated directory structure
    * It traverses the directories, checks cache content metadata, 
      updates the relevant entries in shared memory and 
      then exits when everything is clean and ready for use.
  * cache manager : stay in memory and is restarted by master when fails
    * responsible for cache expiration and invalidation

# makefile
  * order 
    
    GNUmakefile, makefile and Makefile

    variable:MAKEFILES
      global makefiles,split by space, "target" in thoese files take no effect

  * global: *, ? , ~
    ~bob/ same as /home/bob

    objects = *.o # like macro in c
    objects = $(wildcard *.o)

    OBJS = $(SRCS:.c=.o)

  * ignore a makefile
      -include filename
  * add makefie
      include *.md 

  * vpath : search path for make
    1. vpath <pattern> <directories> : match files
    2. vpath <pattern> : clean match files
    3. vpath : clean all files
    ```makefile
    vpath %.c foo:foa
    vpath % blish
    vpath %.c bar
    ```
  * multiple targets
    ```makefile
    bigoutput littleoutput : text.g
      generate text.g -$(subst output,,$@) > $@

    # same as
    bigoutput : text.g
      generate text.g -big > bigoutput
    littleoutput : text.g
      generate text.g -little > littleoutput
    ```

  * static pattern
    ```makefile
    <targets ...> : <target-pattern> : <prereq-patterns ...>
      <commands>

    objects = foo.o bar.o
      all: $(objects)
    $(objects): %.o: %.c
      $(CC) -c $(CFLAGS) $< -o $@

    foo.o : foo.c
        $(CC) -c $(CFLAGS) foo.c -o foo.o
    bar.o : bar.c
        $(CC) -c $(CFLAGS) bar.c -o bar.o


    files = foo.elc bar.o lose.o
    $(filter %.o,$(files)): %.o: %.c
      $(CC) -c $(CFLAGS) $< -o $@
    $(filter %.elc,$(files)): %.elc: %.el
      emacs -f batch-byte-compile $<
    
    ```

    * display
      @echo 

      make -n/--just-print : only show command 
      make -s/--silent : supress all dispaly
    
    * execute: fork a shell to execute cmd
      write the command in one line if you want the later executed based on the fronter

      ```makefile
        exec:
          cd /home/;pwd # print /home
        
        extc:
          cd /home
          pwd
        # print the cwd
      ```

    * error handle
      -rm -f not-exits # ignore rm error
      make -i/--ignore-errors
      make -k/--keep-going :stop current target, go to next target

    * nesting
      ```makefile
      subsystem:
        cd subdir && $(MAKE)

      # same as
      subsystem:
        $(MAKE) -C subdir
    
    * export: pass value to sub makefile
    ```
      export variable := value

      variable = value
      export variable      

      export  # export all variables to sub makefiles
    ```

      __SHELL and MAKEFLAGS are always passed to sub Makfiles __

      -C , -f , -h, -o 和 -W/--print-directory
      when use -C , -w is auto enables unless use -s/--silent or --no-print-directory

    * package
      define run-yacc 
        yacc $(firstwork $^)
        mv y.tab.c $@
      endef

      foo.c : foo.y
        $(run-yacc)

      

  * $@ is the name of the target.
    ```makefile
    client: client.c
        $(CC) client.c -o $@

    server: server.c
        $(CC) server.c -o $@
    ```
  * $? macro stores the list of dependents more recent than the target 
  (i.e., those that have changed since the last time make was invoked for the given target)
    ```makefile
    client: client.c
        $(CC) $? -o $@

    server: server.c
        $(CC) $? -o $@
    ```
  * $^ gives you all dependencies, regardless of whether they are more recent than the target. 
      Duplicate names, however, will be removed. 
      This might be useful if you produce transient output 
      (such as displaying a result to the screen rather than saving it to a file). 
      ```makefile
      # print the source to the screen
      viewsource: client.c server.c
      less $^
      ```
  * $+ is like $^, but it keeps duplicates and gives you the entire list of dependencies in the order they appear.
    ```makefile
    # print the source to the screen
    viewsource: client.c server.c
            less $+
    ```

# kernel
  * [RCU](https://www.kernel.org/doc/Documentation/RCU/whatisRCU.txt)
    http://www2.rdrop.com/users/paulmck/RCU/ 
    The basic idea behind RCU is to split updates into "removal" and "reclamation" phases.
    Splitting the update into removal and reclamation phases permits the
    updater to perform the removal phase immediately, and to defer the
    reclamation phase until all readers active during the removal phase have
    completed, either by blocking until they finish or by registering a
    callback that is invoked after they finish.

      Holding a reference from one RCU read-side critical section
    to another is just as illegal as holding a reference from
    one lock-based critical section to another!  Similarly,
    using a reference outside of the critical section in which
    it was acquired is just as illegal as doing so with normal
    locking.

      The following diagram shows how each API communicates among the
reader, updater, and reclaimer.
      ```
	          rcu_assign_pointer()
	    			                        +--------+
            +---------------------->| reader |---------+
            |                       +--------+         |
            |                           |              |
            |                           |              | Protect:
            |                           |              | rcu_read_lock()
            |                           |              | rcu_read_unlock()
            |        rcu_dereference()  |              |
       +---------+                      |              |
       | updater |<---------------------+              |
       +---------+                                     V
            |                                    +-----------+
            +----------------------------------->| reclaimer |
                                                 +-----------+
              Defer:
              synchronize_rcu() & call_rcu()
       ```

       This section shows a simple use of the core RCU API to protect a
       global pointer to a dynamically allocated structure.  More-typical
       uses of RCU may be found in listRCU.txt, arrayRCU.txt, and NMI-RCU.txt.
       ```c
          struct foo {
            int a;
            char b;
            long c;
          };
          DEFINE_SPINLOCK(foo_mutex);

          struct foo __rcu *gbl_foo;

          /*
          * Create a new struct foo that is the same as the one currently
          * pointed to by gbl_foo, except that field "a" is replaced
          * with "new_a".  Points gbl_foo to the new structure, and
          * frees up the old structure after a grace period.
          *
          * Uses rcu_assign_pointer() to ensure that concurrent readers
          * see the initialized version of the new structure.
          *
          * Uses synchronize_rcu() to ensure that any readers that might
          * have references to the old structure complete before freeing
          * the old structure.
          */
          void foo_update_a(int new_a)
          {
            struct foo *new_fp;
            struct foo *old_fp;

            new_fp = kmalloc(sizeof(*new_fp), GFP_KERNEL);
            spin_lock(&foo_mutex);
            old_fp = rcu_dereference_protected(gbl_foo, lockdep_is_held(&foo_mutex));
            *new_fp = *old_fp;
            new_fp->a = new_a;
            rcu_assign_pointer(gbl_foo, new_fp);
            spin_unlock(&foo_mutex);
            synchronize_rcu();
            kfree(old_fp);
          }

          /*
          * Return the value of field "a" of the current gbl_foo
          * structure.  Use rcu_read_lock() and rcu_read_unlock()
          * to ensure that the structure does not get deleted out
          * from under us, and use rcu_dereference() to ensure that
          * we see the initialized version of the structure (important
          * for DEC Alpha and for people reading the code).
          */
          int foo_get_a(void)
          {
            int retval;

            rcu_read_lock();
            retval = rcu_dereference(gbl_foo)->a;
            rcu_read_unlock();
            return retval;
          }
       ```
       So, to sum up:
        
       * Use rcu_read_lock() and rcu_read_unlock() to guard RCU
          read-side critical sections.

       * Within an RCU read-side critical section, use rcu_dereference()
          to dereference RCU-protected pointers.

       *	Use some solid scheme (such as locks or semaphores) to
          keep concurrent updates from interfering with each other.

       * Use rcu_assign_pointer() to update an RCU-protected pointer.
          This primitive protects concurrent readers from the updater,
          -not- concurrent updates from each other!  You therefore still
          need to use locking (or something similar) to keep concurrent
          rcu_assign_pointer() primitives from interfering with each other.

       *  Use synchronize_rcu() -after- removing a data element from an
          RCU-protected data structure, but -before- reclaiming/freeing
          the data element, in order to wait for the completion of all
          RCU read-side critical sections that might be referencing that
          data item.


  * intall
    * [download tar.gz](https://www.kernel.org/pub/linux/kernel/) 

    * uncompress
      tar -jzxv linux-2.6.34.tar.bz2

    * make defconfig 

    * make oldconfig

    * make -j2

    * make modules_install

    * cp bzImage to root
      ```bash
      cp arch/x86_64/boot/bzImage  /boot/vmlinuz-2.6.34.el6.x86_64
      chmod +x /boot/vmlinuz-2.6.34.el6.x86_64
      ```
    * cp system.map
      ```bash
      cp System.map /boot/System.map-2.6.34.el6.x86_64
      ```

    * mkinitrd /boot/initramfs-2.6.34.el6.x86_64.img 2.6.34

    * grub
      ```bash
      cp /boot/grub/grub.conf /boot/grub/grub.conf.bak
      title CentOS (2.6.34.el6.x86_64)
        root (hd0,0)
        kernel /vmlinuz-2.6.34.el6.x86_64 ro root=/dev/mapper/VolGroup-lv_root rd_NO_LUKS LANG=en_US.UTF-8 rd_NO_MD rd_LVM_LV=VolGroup/lv_swap SYSFONT=latarcyrheb-sun16 crashkernel=auto rd_LVM_LV=VolGroup/lv_root  KEYBOARDTYPE=pc KEYTABLE=us rd_NO_DM rhgb quiet
        initrd /initramfs-2.6.34.el6.x86_64.img
      ```

    * initrd:
      he kernel then can use /dev/initrd’s contents for a two-phase system boot-up
      1. boot-up  phase:the kernel starts up and mounts an initial root file-system from the contents of
       /dev/initrd (e.g., RAM disk initialized by the boot loader)
      
      2. additional drivers  or  other modules  are  loaded  from the initial root device’s contents.
      gunzip initramfs.img.gz
      mkdir initramfs
      cd initramfs
      cpio -idv < ../initramfs.img

      find . | cpio --create --format='newc' > /tmp/newinitrd
      gzip newinitrd 
  
  * gdb
    gdb --args bochs-bin -q -f bochsrc

  * git
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

      
* service configuration
  * dns server configuration bind
   
    1. records
      * SOA record
        start of authority, Indicates authority for this zone
      * NS record
        Lists a nameserver for this zone
      * Other records
        Data about hosts in this zone Of the other records, this chapter covers:
      * A
        Name-to-address mapping
      * PTR
        Address-to-name mapping
      * CNAME
        Canonical name (for aliases)
        
    2. types
        name    | description
        --      | -----------
        TYPE    |        value and meaning
        A       |        1 a host address
        NS      |        2 an authoritative name server
        MD      |        3 a mail destination (Obsolete - use MX)
        MF      |        4 a mail forwarder (Obsolete - use MX)
        CNAME   |        5 the canonical name for an alias
        SOA     |        6 marks the start of a zone of authority
        MB      |        7 a mailbox domain name (EXPERIMENTAL)
        MG      |        8 a mail group member (EXPERIMENTAL)
        MR      |        9 a mail rename domain name (EXPERIMENTAL)
        NULL    |        10 a null RR (EXPERIMENTAL)
        WKS     |        11 a well known service description
        PTR     |        12 a domain name pointer
        HINFO   |        13 host information
        MINFO   |        14 mailbox or mail list information
        MX      |        15 mail exchange
        TXT     |        16 text strings

    3. QTYPE values:QTYPE fields appear in the question part of a query.  QTYPES are a superset of TYPEs, hence all TYPEs are valid QTYPEs.
      name      |     description
      ----      | ------------
      AXFR      |      252 A request for a transfer of an entire zone
      MAILB     |      253 A request for mailbox-related records (MB, MG or MR)
      MAILA     |      254 A request for mail agent RRs (Obsolete - see MX)
      *         |      255 A request for all records

    4. CLASS values:CLASS fields appear in resource records.  The following CLASS mnemonics and values are defined:
      name    | description 
      ----    | ----------
      IN      |    1 the Internet
      CS      |    2 the CSNET class (Obsolete - used only for examples in some obsolete RFCs)
      CH      |    3 the CHAOS class
      HS      |    4 Hesiod [Dyer 87]

    5. QCLASS values:QCLASS fields appear in the question section of a query.  QCLASS values are a superset of CLASS values; 
      every CLASS is a valid QCLASS.  In addition to CLASS values, the following QCLASSes are defined: 
      name    | description
      ---     | -----------
      *       |  255 any class

    6. syntax
      1. comment: ;
      2. directives: $  $ttl, $origin
      3. resource record(RR): 
      4. field seperater: table or space

    7. sample
      ```
      ; IPv4 zone file for example.com
      $TTL 2d ; default TTL for zone
      $ORIGIN example.com. ; base domain-name
      ; Start of Authority record defining the key characteristics
      ; of the zone (domain)
      @ IN SOA ns1.example.com. hostmaster.example.com. (
              2003080800 ; se = serial number
              12h ; ref = refresh
              15m ; ret = refresh retry
              3w ; ex = expiry
              2h ; nx = nxdomain ttl
              )
      ; name servers Resource Records for the domain
      IN NS ns1.example.com.
      ; the second name server is
      ; external to this zone (domain).
      IN NS ns2.example.net.
      ; mail server Resource Records for the zone (domain)
      ; value 10 denotes it is the most preferred
      3w  IN  MX  10 mail.example.com.
      ; the second mail server has lower preference (20) and is
      ; external to the zone (domain)
          IN  MX  20 mail.example.net.
      ; domain hosts includes NS and MX records defined previously
      ; plus any others required
      ns1     IN   A     192.168.254.2
      mail    IN   A     192.168.254.4
      joe     IN   A     192.168.254.6
      www     IN   A     192.168.254.7
      ; aliases ftp (ftp server) to an external location
      ftp IN CNAME ftp.example.net.
      ```
      * $TTL directive: time to live for a zone or domain, which is the time a RR may be cached by another server, mandatory
        * access load: lower TTL means more frequent dns queries to occur.
        * change propagate: TTL represents max time that a propagate will take from the zone name server to users.

      * $ORIGIN directive: the domain name for the zone defined, optional
        * defines the domain name that will be appended to any incomplete name (sometimes called an unqualified name) defined in an RR
        * The $ORIGIN Substitution Rule If a name appears in a RR and does not end with a dot, then the value of the last or only $ORIGIN 
          directive will be appended to the name. If the name ends with a dot, then it is a fully qualified domain name (FQDN) and nothing will be appended
      * A start of authority(SOA) RR: must be first RR in a zone file, descript the feathures of zone or domain, only one, mondatory
        * SOA RR syntax:
          @   IN  ns1.example.com   hostmaster.example.com (
              2003080800 ; se = serial number
              12h ; ref = refresh
              15m ; ret = refresh retry
              3w ; ex = expiry
              2h ; nx = nxdomain ttl
          )
          syntax         |          name           | description
          ------         | ---- | -----------
           name          |   @  | substitutes the current value of $ORIGIN (in the example file this is example.com.).
           ttl           |      |  There is no ttl value defined for the RR, so the zone default of 2d (172800 seconds) from the $TTL directive will be used.
           class         | IN   |  IN defines the class to be Internet (defaulted if omitted). Other values exist but are rarely used. 
           name-server   | ns1.example.com. | Defines the Primary Master name server for the zone, MNAME
           email         | hostmaster.example.com. |  Defines an administrative e-mail address for the zone. mail will be sent to hostmaster@example.com. RNAME 
           sn            | 2003080800 | must be updated each time changes made to the domain, by convention yyyymmddss
           refresh       | 12h        | when time reached, slave name server for this zone will try to read the SOA RR from the zone, 3-24h
           retry         | 15m        | retry interval when slave fails to contact with master, 10-60mh
           expire        | 3w         | If the slave failed to contact when expiry reached, the slave will stop responding to any queries. The zone is dead.
           nx            | 3h         | rfc 2308, the period of time that negative responses can be cached by a resolver. 0-10800(3 hours)

           email sn refresh refresh expire nxdomain ttl

      * name server(NS) RR: define NS that are authority for the zone or domain, >= 2, NS RR may refercens servers on same domain, or in a foreign or external
        domain, mandotory.
        * zone        ttl   class rr name-server
          movie.edu           IN  NS toystory.movie.edu.
          movie.edu.          IN  NS wormhole.movie.edu.
          These records indicate that there are two nameservers for the zone movie.edu. 

      * Mail Exchanger(MX) RR: Define mail servers for the zone, >= 0, on the same domain or external domain, optional.
        * name ttl class  rr preference     name
                3w  IN    MX    10        mail.example.com

      * Address(A) RR: define IPv4 address of all hosts or services, publicity visible, AAAA(call Quad A) RR for IPv6,  >=0, optional
        * name ttl class rr ipv4

      * Conanical Name(CNAME) RR: alias for another host, >=0, optional
        * name ttl class rr canonical-name

      * PTR RR: reverse-mapping, address to hostname
        * address     ttl           class type      hostname
        1.249.249.192.in-addr.arpa.   IN   PTR   wormhole.movie.edu.
        2.249.249.192.in-addr.arpa.   IN   PTR   shrek.movie.edu.
        3.249.249.192.in-addr.arpa.   IN   PTR   toystory.movie.edu.
        4.249.249.192.in-addr.arpa.   IN   PTR   monsters-inc.movie.edu.
      
      * full example:
        ```
        db.movie.edu:
        $TTL 3h
        movie.edu. IN SOA toystory.movie.edu. al.movie.edu. (
              81
              811 ; Serial
              3h ; Refresh after 3 hours
              1h ; Retry after 1 hour
              1w ; Expire after 1 week
              1h ) ; Negative caching TTL of 1 hour
        ;
        ; Name servers
        ;
        movie.edu. IN NS toystory.movie.edu.
        movie.edu. IN NS wormhole.movie.edu.
        ;
        ; Addresses for the canonical names
        ;
        localhost.movie.edu.    IN A 127.0.0.1
        shrek.movie.edu.        IN A 192.249.249.2
        toystory.movie.edu.     IN A 192.249.249.3
        monsters-inc.movie.edu. IN A 192.249.249.4
        misery.movie.edu.       IN A 192.253.253.2
        shining.movie.edu.      IN A 192.253.253.3
        carrie.movie.edu.       IN A 192.253.253.4
        wormhole.movie.edu.     IN A 192.249.249.1
        wormhole.movie.edu.     IN A 192.253.253.1
        ;
        ; Aliases
        ;
        toys.movie.edu. IN CNAME toystory.movie.edu.
        mi.movie.edu.   IN CNAME monsters-inc.movie.edu.
        wh.movie.edu.   IN CNAME wormhole.movie.edu.
        ;
        ; Interface specific names
        ;
        wh249.movie.edu. IN A 192.249.249.1
        wh253.movie.edu. IN A 192.253.253.1

        db.192.249.249:
        $TTL 3h
        249.249.192.in-addr.arpa. IN SOA toystory.movie.edu. al.movie.edu.(
              1 ; Serial
              3h ; Refresh after 3 hours
              1h ; Retry after 1 hour
              1w ; Expire after 1 week
              1h ) ; Negative caching TTL of 1 hour
              ;
        ; Name servers
        ;
        249.249.192.in-addr.arpa. IN NS toystory.movie.edu.
        249.249.192.in-addr.arpa. IN NS wormhole.movie.edu.
        ;
        ; Addresses point to canonical name
        ;
        1.249.249.192.in-addr.arpa. IN PTR wormhole.movie.edu.
        2.249.249.192.in-addr.arpa. IN PTR shrek.movie.edu.
        3.249.249.192.in-addr.arpa. IN PTR toystory.movie.edu.
        4.249.249.192.in-addr.arpa. IN PTR monsters-inc.movie.edu.

        b.127.0.0:
        $TTL 3h
        0.0.127.in-addr.arpa. IN SOA toystory.movie.edu. al.movie.edu. (
                1 ; Serial
                3h ; Refresh after 3 hours
                1h ; Retry after 1 hour
                1w ; Expire after 1 week
                1h  ; Negative caching TTL of 1 hour
             )
        0.0.127.in-addr.arpa. IN NS toystory.movie.edu.
        0.0.127.in-addr.arpa. IN NS wormhole.movie.edu.
        1.0.0.127.in-addr.arpa. IN PTR localhost.
        ```

      * my configuration
        * install [bind] 
          ```
          https://www.ietf.org/rfc/rfc1035.txt
          http://cymru.com/Documents/secure-bind-template.html
          yum install bind bind-utils bind-chroot -y
          ```
        * namde conf
          ```
          cat /etc/named.conf
          //
          // named.conf
          //
          // Provided by Red Hat bind package to configure the ISC BIND named(8) DNS
          // server as a caching only nameserver (as a localhost DNS resolver only).
          //
          // See /usr/share/doc/bind*/sample/ for example named configuration files.
          //

          acl deny-net {
              0.0.0.0/8;
              192.0.2.0/24;
              224.0.0.0/3;
              10.0.0.0/8;
              172.16.0.0/12;
          };

          acl allow-net {
              192.168.2.0/24;
          };

          acl axfr {
              192.168.2.135;
          };

          options {
            listen-on port 53 { 192.168.2.131; };
            listen-on-v6 port 53 { ::1; };
            directory 	"/var/named";
            dump-file 	"/var/named/data/cache_dump.db";
                  statistics-file "/var/named/data/named_stats.txt";
                  memstatistics-file "/var/named/data/named_mem_stats.txt";

            allow-query     { allow-net; };
              allow-query-cache { allow-net; };
              allow-recursion { allow-net; };
              allow-transfer  {
                  axfr;
              };
              // recursion yes;
              blackhole   {deny-net; };

              // Prevent DoS attacks by generating bogus zone transfer
              // requests.  This will result in slower updates to the
              // slave servers (e.g. they will await the poll interval
              // before checking for updates).
              notify no;

              // Generate more efficient zone transfers.  This will place
              // multiple DNS records in a DNS message, instead of one per
              // DNS message.
              transfer-format many-answers;

              // Set the maximum zone transfer time to something more
              // reasonable.  In this case, we state that any zone transfer
              // that takes longer than 60 minutes is unlikely to ever
              // complete.  WARNING:  If you have very large zone files,
              // adjust this to fit your requirements. 
              max-transfer-time-in 60;

              // We have no dynamic interfaces, so BIND shouldn't need to
              // poll for interface state {UP|DOWN}.
              interface-interval 0;

            dnssec-enable yes;
            dnssec-validation yes;

            /* Path to ISC DLV key */
            bindkeys-file "/etc/named.iscdlv.key";

            managed-keys-directory "/var/named/dynamic";
          };

          logging {
                  channel default_debug {
                          file "data/named.run";
                          severity dynamic;
                  };

                  channel audit_log {
                      file "data/name.log";
                      severity debug;
                      print-time yes;
                  };

                  category default { default_debug;};
                  category general { default_debug; };
                  category security { audit_log; default_debug; };
                  category config { default_debug; };
                  category resolver { audit_log; };
                  category xfer-in { audit_log; };
                  category xfer-out { audit_log; };
                  category notify { audit_log; };
                  category client { audit_log; };
                  category network { audit_log; };
                  category update { audit_log; };
                  category queries { audit_log; };
                  category lame-servers { audit_log; };
          };


          view "internal-in" IN {
              match-clients {allow-net;};

              // recursion yes;
              additional-from-auth yes;
              additional-from-cache yes;

              zone "." IN {
                  type hint;
                  file "named.ca";
              };

              include "/etc/named.rfc1912.zones";

              zone "dob.com" IN {            
                  type master;
                  file "dob.com.db";
                  allow-update { none; };
                  allow-query { allow-net; };
              };
          };


          view "external-in" in {
              match-clients { any; };
              // recursion no;
              additional-from-auth no;
              additional-from-cache no;

              zone "." in {
                  type hint;
                  file "named.ca";
              };

              include "/etc/named.rfc1912.zones";
          };

          view "external-chaos" chaos {
              match-clients {any;};
              recursion no;

              zone "." {
                  type hint;
                  file "/dev/null";
              };

              zone "bind" {
                  type master;
                  file "db.bind";

                  allow-query {
                      allow-net;
                  };

                  allow-transfer {
                      none;
                  };
              };
          };


          include "/etc/named.root.key";

          ```
        
        * dob.com.bd
          ```
          cat `pwd`/dob.com.db
          ; IPv4 zone file for dob.com
          $TTL 2d ; default TTL for zone
          $ORIGIN dob.com.
          ; Start of Authority record defining the key characteristics of the zone (domain)
          @ IN SOA ns1.dob.com. centos.dob.com. (
                  2003080800 ; sn = serial number
                  12h ; refresh
                  15m ; retry = refresh retry
                  3w ; expiry
                  2h ; nx = nxdomain ttl
                  )
          ; name servers Resource Records for the domain
              IN NS ns1.dob.com.
          ; the second name servers is
          ; external to this zone (domain).
          ;    IN NS ns2.dob.net.
          ; mail server Resource Records for the zone (domain)
          3w IN MX 10 mail.dob.com.
          ; the second mail servers is
          ; external to the zone (domain)
          ; IN MX 20 mail.anotherdomain.com.
          ; domain hosts includes NS and MX records defined above
          ; plus any others required
          ns1     IN  A 192.168.2.131
          mail    IN  A 192.168.2.131
          www     IN  A 192.168.2.131
          centos    IN  CNAME ns1.dob.com.
          ```

          db.bind
          ```
          cat db.bind
          ;@(#) db.bind v1.2 25 JAN 2001 Team Cymru Thomas noc@cymru.com
          ;
          $TTL 1D
          $ORIGIN bind.
          @   1D  CH   SOA localhost. root.localhost. (
                  2017021217  ; serial number
                  3h  ; refresh
                  1h  ; retry
                  1w  ; expire
                  1d  ; nxmain
                  )
              CH   NS  localhost.

          version CH   TXT "BIND 9"
          authors CH   TXT "LA LA LA LA. :)"
          ```

        * start service and configure autostart
          ```bash
          service named restart
          chkconfig named on

          iptables -t filter -I INPUT -p tcp -s 192.168.0.0/16 --dport 53 -j ACCEPT
          iptables -t filter -I INPUT -p udp -s 192.168.0.0/16 --dport 53 -j ACCEPT
          service iptalbes save
          ```
        
        * test 
          ```bash
          dig @192.168.2.131  ns1.dob.com -t any

          dig @192.168.2.131 dob.com axfr
            ; <<>> DiG 9.8.2rc1-RedHat-9.8.2-0.47.rc1.el6_8.4 <<>> @192.168.2.131 dob.com axfr
            ; (1 server found)
            ;; global options: +cmd
            dob.com.		172800	IN	SOA	ns1.dob.com. centos.dob.com. 2003080800 43200 900 1814400 7200
            dob.com.		172800	IN	NS	ns1.dob.com.
            dob.com.		1814400	IN	MX	10 mail.dob.com.
            centos.dob.com.		172800	IN	CNAME	ns1.dob.com.
            mail.dob.com.		172800	IN	A	192.168.2.131
            ns1.dob.com.		172800	IN	A	192.168.2.131
            www.dob.com.		172800	IN	A	192.168.2.131
            dob.com.		172800	IN	SOA	ns1.dob.com. centos.dob.com. 2003080800 43200 900 1814400 7200
            ;; Query time: 1 msec
            ;; SERVER: 192.168.2.131#53(192.168.2.131)
            ;; WHEN: Sun Feb 12 02:35:04 2017
            ;; XFR size: 8 records (messages 1, bytes 209)
          ```
  * dpkg
    * dpkg --force-all --purge texlive-base
      dpkg --purge snmpcheck
      dpkg --install 
      apt-get upgrade -s -f

      apt-get -f update
    
    * dpkg error:
      ```
      * apt-get update
        .......
        dpkg: dependency problems prevent processing triggers for man-db:
        man-db depends on bsdmainutils; however:
          Package bsdmainutils is not configured yet.

        dpkg: error processing archive /var/cache/apt/archives/libpam-modules_1.1.8-3.5_amd64.deb (--unpack):
        dependency problems - leaving triggers unprocessed
        Errors were encountered while processing:
        /var/cache/apt/archives/libpam-modules_1.1.8-3.5_amd64.deb
        E: Sub-process /usr/bin/dpkg returned an error code (1)

      * apt-get install bsdmainutils
        Reading package lists... Done
        Building dependency tree       
        Reading state information... Done
        bsdmainutils is already the newest version.
        You might want to run 'apt-get -f install' to correct these:
        The following packages have unmet dependencies:
        libpam-modules : PreDepends: libpam-modules-bin (= 1.1.3-7.1) but 1.1.8-3.5 is to be installed
        E: Unmet dependencies. Try 'apt-get -f install' with no packages (or specify a solution).

      * dpkg --force-downgrade --install libpam-modules-bin-1.1.3-7.1

      * apt-cache showpkg libpam-modules-bin
        Package: libpam-modules-bin
        Versions: 
        1.1.8-3.5 (/var/lib/apt/lists/http.kali.org_kali_dists_kali-rolling_main_binary-amd64_Packages)
        Description Language: 
                        File: /var/lib/apt/lists/http.kali.org_kali_dists_kali-rolling_main_binary-amd64_Packages
                          MD5: 25d278fc7450d5202a9a137f71302e58


        Reverse Depends: 
          libpam-modules,libpam-modules-bin 1.1.3-7.1
          libpam-modules,libpam-modules-bin 1.1.8-3.5
        Dependencies: 
        1.1.8-3.5 - libaudit1 (2 1:2.2.1) libc6 (2 2.14) libpam0g (2 0.99.7.1) libselinux1 (2 1.32) libpam-modules (3 1.1.3-8) 
        Provides: 
        1.1.8-3.5 - 
        Reverse Provides: 

      * apt-cache policy libpam-modules-bin
        libpam-modules-bin:
        Installed: (none)
        Candidate: 1.1.8-3.5
        Version table:
          1.1.8-3.5 0
              500 http://http.kali.org/kali/ kali-rolling/main amd64 Packages
        
        apt-get install libpam-modules-bin=1.1.3-7.1
      ```

  * network connection error
    * eth0 eth1
      * ifconfig eth1 down
        ifconfig eth0 down
      * ifconfig eth0 up
      
      * tcpdump -i any -vvv &> /tmp/tcpdump.log
        dhclient -4 -p 68 -s 255.255.255.255 -d -v 

        strace -f -e verbose=a trace=process,file -s 128 ifup eth1
        /sbin/dhclient [/sbin/dhclient -4 -v -pf /run/dhclient.eth1.pid -lf /var/lib/dhcp/dhclient.eth1.leases -I -df /var/lib/dhcp/dhclient6.eth1.leases eth1]

      * dpkg -S /sbin/dhclient
        isc-dhcp-client: /sbin/dhclient
        
  * tftp server configure
    * yum install xinetd tftp tftp-server -y
    
    * configure tftp:
      ```
      cat /etc/xinetd.d/tftp 
      # default: off
      # description: The tftp server serves files using the trivial file transfer \
      #	protocol.  The tftp protocol is often used to boot diskless \
      #	workstations, download configuration files to network-aware printers, \
      #	and to start the installation process for some operating systems.
      service tftp
      {
        socket_type		= dgram
        protocol		  = udp
        port          = 69
        wait			    = yes
        user			    = root
        server			  = /usr/sbin/in.tftpd
        server_args		= -s /var/lib/tftpboot # root directory 
        disable			  = yes
        per_source		= 11
        cps			      = 100 2
        flags			    = IPv4
      }
      ```
    
    * service xinetd restart
      iptables -t filter -I INPUT -p udp -s 192.168.0.0/16 --dport 69 -j ACCEPT
    
    * tftp:
      ```bash
      tftp 192.168.2.131
      tftp> verbose
      Verbose mode on.
      tftp> trace
      Packet tracing on.
      tftp> get test
      getting from 192.168.2.131:test to test [netascii]
      sent RRQ <file=test, mode=netascii>
      received DATA <block=1, 0 bytes>
      tftp> get /etc/passwd /tmp/passwd.copy
      getting from 192.168.2.131:/etc/passwd to /tmp/passwd.copy [netascii]
      sent RRQ <file=/etc/passwd, mode=netascii>
      received ERROR <code=1, msg=File not found>
      Error code 1: File not found
      ```
    
  - [tcp wrappers](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/6/html/Security_Guide/sect-Security_Guide-TCP_Wrappers_and_xinetd-TCP_Wrappers_Configuration_Files.html):
    - configure:<daemon list> : <client list> [: <option> : <option> : …]
       ```
        sshd : .example.com  \
        : spawn /bin/echo `/bin/date` access denied>>/var/log/sshd.log \
        : deny
       ```
      - daemon list> — A comma-separated list of process names (not service names) or the ALL wildcard.
      - client list> — A comma-separated list of hostnames, host IP addresses, special patterns, or wildcards which identify the hosts affected by the rule.
      - option> — An optional action or colon-separated list of actions performed when the rule is triggered. 
        1. Wildcards:
           - ALL — Matches everything. It can be used for both the daemon list and the client list.
           - LOCAL — Matches any host that does not contain a period (.), such as localhost.
           - KNOWN — Matches any host where the hostname and host address are known or where the user is known.
           - UNKNOWN — Matches any host where the hostname or host address are unknown or where the user is unknown.
           - PARANOID — A reverse DNS lookup is done on the source IP address to obtain the host name. Then a DNS lookup is performed to resolve the IP address.
             If the two IP addresses do not match the connection is dropped and the logs are updated 
        2. patterns: 
          ```
          1.  beginning with a period (.) 
            ALL : .example.com
          2. ending with a period (.) 
            ALL : 192.168.
          3. IP address/netmask pair
            ALL : 192.168.0.0/255.255.254.0
          4. [IPv6 address]/prefixlen pair — [net]/prefixlen pairs
            ALL : [3ffe:505:2:1::]/64
          5. he asterisk (*) 
            ALL : *.example.com
          6. The slash (/) 
            in.telnetd : /etc/telnet.hosts
          ```
        3. expansions:
          - %a — Returns the client's IP address.
          - %A — Returns the server's IP address.
          - %c — Returns a variety of client information, such as the user name and hostname, or the user name and IP address.
          - %d — Returns the daemon process name.
          - %h — Returns the client's hostname (or IP address, if the hostname is unavailable).
          - %H — Returns the server's hostname (or IP address, if the hostname is unavailable).
          - %n — Returns the client's hostname. If unavailable, unknown is printed. If the client's hostname and host address do not match, paranoid is printed.
          - %N — Returns the server's hostname. If unavailable, unknown is printed. If the server's hostname and host address do not match, paranoid is printed.
          - %p — Returns the daemon's process ID.
          - %s —Returns various types of server information, such as the daemon process and the host or IP address of the server.
          - %u — Returns the client's user name. If unavailable, unknown is printed. 
      - step: take effect immediately when files changes
        1. /etc/hosts.allow
          ```
          in.tftpd: LOCAL
          ```
        2. /etc/host.deny
          ```
          in.tftpd: ALL: spawn (/usr/sbin/safe_finger -l @%h | \
                       /usr/ucb/mail -s %d-%h root) &
          ```
  - snmp 
    ```
    service snmpd start
    iptables -t filter -I INPUT -p udp -s 192.168.0.0/16 --dport 161 -j ACCEPT
    service iptables save

    snmpcmd:
      # community:public snmp-version 1, 2c, 3
      snmpwalk -c public -v 2c 192.168.2.131
        iso.3.6.1.2.1.1.1.0 = STRING: "Linux centos.dob.com 2.6.32-642.11.1.el6.x86_64 #1 SMP Fri Nov 18 19:25:05 UTC 2016 x86_64"
        iso.3.6.1.2.1.1.2.0 = OID: iso.3.6.1.4.1.8072.3.2.10
        iso.3.6.1.2.1.1.3.0 = Timeticks: (228904) 0:38:09.04
        iso.3.6.1.2.1.1.4.0 = STRING: "Root <root@localhost> (configure /etc/snmp/snmp.local.conf)"
        iso.3.6.1.2.1.1.5.0 = STRING: "centos.dob.com"
        iso.3.6.1.2.1.1.6.0 = STRING: "Unknown (edit /etc/snmp/snmpd.conf)"
        iso.3.6.1.2.1.1.8.0 = Timeticks: (67) 0:00:00.67
        iso.3.6.1.2.1.1.9.1.2.8 = OID: iso.3.6.1.6.3.16.2.2.1
        iso.3.6.1.2.1.1.9.1.3.1 = STRING: "The MIB for Message Processing and Dispatching."
        iso.3.6.1.2.1.1.9.1.3.2 = STRING: "The MIB for Message Processing and Dispatching."
        iso.3.6.1.2.1.1.9.1.3.3 = STRING: "The SNMP Management Architecture MIB."
        iso.3.6.1.2.1.1.9.1.3.4 = STRING: "The MIB module for SNMPv2 entities"
        iso.3.6.1.2.1.1.9.1.3.5 = STRING: "The MIB module for managing TCP implementations"
        iso.3.6.1.2.1.1.9.1.3.6 = STRING: "The MIB module for managing IP and ICMP implementations"
        iso.3.6.1.2.1.1.9.1.3.7 = STRING: "The MIB module for managing UDP implementations"
        iso.3.6.1.2.1.1.9.1.3.8 = STRING: "View-based Access Control Model for SNMP."
        iso.3.6.1.2.1.25.1.1.0 = Timeticks: (955530) 2:39:15.30
        End of MIB
     ```

# vpn server 
  1. install packages 
    ```
    yum install wget bind-utils
    ```

  2. install epel repository for xl2tpd package
    ```
    yum install openswan xl2tpd ppp lsof
    ```

  3. firewall and sysctl
    ```bash
    iptables -t nat -A POSTROUTING -j MASQUERADE

    enable kernel IP packet forwarding and disable ICP redirects.

    echo "net.ipv4.ip_forward = 1" |  tee -a /etc/sysctl.conf
    echo "net.ipv4.conf.all.accept_redirects = 0" |  tee -a /etc/sysctl.conf
    echo "net.ipv4.conf.all.send_redirects = 0" |  tee -a /etc/sysctl.conf
    for vpn in /proc/sys/net/ipv4/conf/*; do echo 0 > $vpn/accept_redirects; echo 0 > $vpn/send_redirects; done
    sysctl -p

    iptables -t filter -I INPUT -p udp -m multiport --dports 500,1701 -j ACCEPT   


    
