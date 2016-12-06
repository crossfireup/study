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
    iptables -t nat -I PREROUTING -t tcp -dport 8888 -j REDIRECT --to 80
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

        :noh

        Or turn off highlighting completely:

        set nohlsearch

        Or, to toggle it:

        set hlsearch!

        nnoremap <F3> :set hlsearch!<CR>

     * delete
        
        d63G # delete from cursor to line 63
        
        :a,bd # delete from a to b
        
        :,bd # delete from current to d 


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
    
        水平平分（even-horizontal）
        垂直平分（even-vertical）
        主窗格最大化，其他窗格水平平分（main-horizontal）
        主窗格最大化，其他窗格垂直平分（main-vertical）
        平铺，窗格均等分（tiled）

