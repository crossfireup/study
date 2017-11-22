# introduction
    http://www.kegel.com/c10k.html

# [session](https://en.wikipedia.org/wiki/Session_%28computer_science%29)
  session is a semi-permanent interactive information interchange, also known as a dialogue, 
  a conversation or a meeting, between two or more communicating devices, 
  or between a computer and user (see Login session).

  Communication Transport may be implemented as part of protocols and services at the application layer, at the session layer or at the transport layer in the OSI model.

  * Application layer examples:

     * HTTP sessions, which allow associating information with individual visitors
     * A telnet remote login session

  * Session layer example:

    A Session Initiation Protocol (SIP) based Internet phone call

  * Transport layer example:
    
    A TCP session, which is synonymous to a TCP virtual circuit, 
    a TCP connection, or an established TCP socket.

# cgi
  
  * ISAPI (like NSAPI for Netscape or ASAPI for Apache)
    
    The Internet Server Application Programming Interface (ISAPI) is an N-tier API of Internet Information Services (IIS), 
    Microsoft's collection of Windows-based web server services. The most prominent application of IIS and ISAPI is Microsoft's web server.

    he ISAPI has also been implemented by Apache's mod_isapi module so that server-side web applications written for Microsoft's IIS can be used with Apache, 
    and other third-party web servers like Zeus Web Server offer ISAPI interfaces.
  
  * fastcgi vs cgi

    Instead of creating a new process for each request, FastCGI uses persistent processes to handle a series of requests.
     These processes are owned by the FastCGI server, not the web server.

     the separation of web applications from the web server in FastCGI has many advantages over embedded interpreters (mod_perl, mod_php, etc.):
     
       __allows server and application processes to be restarted independently__

       __enables the implementation of per-application / hosting service security policies,
         which is an important requirement for ISPs and web hosting companies__

# vpn
  - referrences
    ```
    http://www.unixwiz.net/techtips/iguide-ipsec.html
    https://technet.microsoft.com/en-us/library/cc779919(d=printer,v=ws.10).aspx
    https://tools.ietf.org/pdf/rfc2637.pdf
    https://technet.microsoft.com/en-us/library/cc771298(v=ws.10).aspx
    ```
  - terminology
    - network access server (NAS):

      A device providing temporary, on-demand network access to users. This access is point-to-point using PSTN or ISDN lines.
    
    - PPTP Access Server (PAC):

      A device attached to one or more PSTN or ISDN lines capable of PPP operation and of handling the PPTP protocol. The PAC need only
      implement TCP/IP to pass traffic to one or more PNSs. It may also tunnel non-IP protocols.

    - PPTP Network Server (PNS)
      
      A PNS is envisioned to operate on general-purpose computing/server platforms. The PNS handles the server side of the PPTP protocol.
      Since PPTP relies completely on TCP/IP and is independent of the interface hardware, the PNS may use any combination of IP interface 
      hardware including LAN and WAN devices.

    -  L2TP Access Concentrator (LAC)

      A node that acts as one side of an L2TP tunnel endpoint and is a peer to the L2TP Network Server (LNS).  The LAC sits between an
      LNS and a remote system and forwards packets to and from each. Packets sent from the LAC to the LNS requires tunneling with the
      L2TP protocol as defined in this document.  The connection from the LAC to the remote system is either local (see: Client LAC) or
      a PPP link.

    - L2TP Network Server (LNS)

      A node that acts as one side of an L2TP tunnel endpoint and is a peer to the L2TP Access Concentrator (LAC).  The LNS is the
      logical termination point of a PPP session that is being tunneled from the remote system by the LAC.
    
    - Management Domain (MD)

      A network or networks under the control of a single administration, policy or system. For example, an LNS's Management
      Domain might be the corporate network it serves. An LAC's Management Domain might be the Internet Service Provider that owns
      and manages it.

    - PSTN (public switched telephone network) 
      the world's collection of interconnected voice-oriented public telephone networks, both commercial and government-owned. 
      It's also referred to as the Plain Old Telephone Service (POTS).

  - architecture of vpn: over public internet, such as Internet; or over a private intranet
    - remote access VPN connection:
      ```
      remote client   -------------------------> vpn server
      authenticate itselt to server           authenticate itself to vpn client
      ```
    - site-to-site(router-to-router) VPN connection
       ```                        VPN connection tunnel
          _____  vpn router _____________________________________ vpn router ______ 
          |                   |                              |                     |
          |                dedicated                    dedicated                  |
          |          or dial-up link to ISP            link to ISP                 |
        clients                                                                 clients

  - vpn tunnel: enables the encapsulation of one type of protocol packet within the datagram of a different protocol
    - PPTP(point-to-point tunnel protocol)
      - use a tcp connection to create, maintain, and terminate the tunnel
      - use a modified version of Generic Routing Encapsulation(GRE) to encapsulate PPP frames as tunneled data
      - the payload of encapsulated PPP frames can be encrypted, compressed, or both
      ```
      PPTP control message:
       --------------------------------------------------------------------------
       | Data-link header | IP header | PPTP control message | Data-link tailer |
       --------------------------------------------------------------------------
      
      Tunneled PPTP data:
      -------------------------------------------------------------------------------------------------------------------
      | Data-link Header | IP header | GRE Header | PPP Header | Encrypted PPP Payloads(IP datagram) | Data-link Tailer |
      -------------------------------------------------------------------------------------------------------------------
      Processing of the tunneled PPTP data. Upon receipt of the tunneled PPTP data, the PPTP client or PPTP server:
        * Processes and removes the data-link header and trailer.
        * Processes and removes the IP header.
        * Processes and removes the GRE and PPP headers.
        * Decrypts and, if needed, decompresses the PPP payload.
        * Processes the payload for receipt or forwarding.
      ```
    - L2TP(layer two tunnel protocol): a combination of PPTP and Layer 2 Forwarding (L2F), a technology developed by Cisco Systems, Inc
      - L2TP encapsulates PPP frames to be sent over IP, X.25, frame relay, or ATM networks
      - when sent over IP network, L2TP frames are encapsulated as UDP messages
      - L2TP uses UDP messages over IP networks for both tunnel maintenance and tunneled data
        The L2TP client and L2TP server in Windows always use UDP port 1701. The Windows Server 2003 L2TP server supports L2TP clients t
        hat use a UDP port other than 1701
      - L2TP clients do not negotiate the use of MPPE for L2TP connections. Encryption for L2TP 
        connections is provided by IPSec Encapsulating Security Payload (ESP) in transport mode.
      ```
      L2TP Control Message
      -------------------------------------------------------------------------------------------------------------------------------------------------------
      | Data-link header | IP header | IPSec ESP header | UDP header | L2TP Message | IPSec ESP tailer | IPSec ESP authentication tailer | Date-link tailer |
      -------------------------------------------------------------------------------------------------------------------------------------------------------
      
      L2TP Packet encapsulation
      -------------------------------------------------------------------------------------------------------------------
      | Data-link |   IP   | IPSec ESP |  UDP   | L2TP   |  PPP   | PPP payloads  | IPSec ESP | IPSec ESP   | Data-link |
      |  header   | header | header    | header | header | header | (IP datagram) | tailer    | auth tailer |  tailer   |
      -------------------------------------------------------------------------------------------------------------------
                           |           |_____________encrypted by IPSec ESP___________________|             |
                           |                                                                                |
                           |________________authenticated by IPSec ESP auth tailer _________________________|
      Processing of the tunneled L2TP/IPSec data. Upon receipt of the tunneled L2TP/IPSec data, the L2TP client or L2TP server:
        * Processes and removes the data-link header and trailer.
        * Processes and removes the IP header.
        * Uses the IPSec ESP Auth trailer to authenticate the IP payload and the IPSec ESP header.
        * Uses the IPSec ESP header to decrypt the encrypted portion of the packet.
        * Processes the UDP header and sends the L2TP packet to the L2TP driver.
        * Uses the Tunnel ID and Call ID in the L2TP header to identify the specific L2TP tunnel.
        * Uses the PPP header to identify the PPP payload and forward it to the proper protocol driver for processing.
      ```                                                             

    - two types of tunneling:
      1. voluntary tunneling
        - user or client computer can issue a VPN request to configure and create a voluntary tunnel
        - the users computer is a tunnel endpoint and acts as the tunnel client.

      2. compulsory tunneling
        - VPN-capable remote access server configures and creates a compulsory tunnel
        - the dial-up access server, between the user's computer and the tunnel server is the tunnel endpoint and acts as the tunnel client.

    - vpn authentication
      - Remote Authentication Dail-In User Server(RADIUS) also known as a AAA transaction that stands for authentication, authorization and accounting.
      - PAP
      - CHAP
      - EAP
      - EAP-md5
      - EAP-TLS

    - ISAKMP is an older implementation of what is known now as IKE. 
      IKE is a combination of ISAKMP, Oakley, SKEME and used for distribution and how to generated of public keys.
      - ISAKMP is a protocol to establish framework authentication and key exchange
      - Oakley (which describes a series of key exchange defining in detail the services provided by them)
      - SKEME (a key exchange technique that provides anonymity, reputability, and quick key refreshment)

- ssl
  - [decrypt](https://wiki.wireshark.org/SSL)

# wireshark
  - Locating the Source of High Latency
    - wire latency: device between the client and server
      syn,ack

    - client latency: client --> server
      - layer7 protocol request

    - server latency: server --> client
      - layer7 protocol data 

  - [DLPI(Data Link Provider Interface)](http://pubs.opengroup.org/onlinepubs/9638599/chap1.htm)
    - enables a data link service user to access and use any of a variety of conforming data link service providers without special knowledge of the provider's protocol. 


  - usage
    ```
    tcpdump -U -v -i eth0 host 192.168.1.1 -w - | tee f.pcap | tcpdump -vvv -lnr -

     tcp contains traffic [displays all TCP packets that contain the word ‘traffic’. Excellent when searching on a specific string or user ID]
    udp contains 33:27:58 [sets a filter for the HEX values of 0x33 0x27 0x58 at any offset]
    ```
  
  - tshark
    - extract server_name in ssl
      ```
      "C:\Program Files\Wireshark\tshark.exe" -r ssl.pcap.pcapng -T fields -e ssl.handshake.extensions_server_name -Y ssl.handshake.extensions_server_name

      "C:\Program Files\Wireshark\tshark.exe" -T json -j "http tcp ip" -x -r file.pcap

      "C:\Program Files\Wireshark\tshark.exe" -Y "dns.flags.response == 1" -T fields -E separator=";" -E quote=s -e frame.time -e dns.qry.name -e dns.a -r file.pcap

      # http post body: http.file_data, text, data.data
      "C:\Program Files\Wireshark\tshark.exe" -Y "http.request.method == POST" -T fields -E separator=";" -E quote=s -e frame.time -e http.host -e http.request.uri -e http.file_data -e text -r file.pcap

      tshark -u s -t ad -o column.format:"Time, %t","Source, %s","Destination, %d","Protocol, %p","Info, %i" 

      tcp.port in {80 443 8080}

      dns.apl.afdpart.ipv4
      ```
    
    - follow stream
      ```
      tshark -z flow,tcp,ascii -r *.pcap
      tshark -z "follow,tcp,ascii,200.57.7.197:32891,200.57.7.198:2906"
      ```

    - testing
      ```
      randpkt -c 50000 -t dns randpkt.pcap

      editcap -E 0.03 in.pcap out.pcap
      ```

    - dns
      ```
      windows:tshark -G currentprefs | find "resolve"
      unix:tshark -G currentprefs | grep "resolve"
      Result: name_resolve: FALSE

      Preferences -> Name Resolution -> Enable Network Name Resolution

      tshark -r input.cap -T fields -e ip.src -e ip.src_host -e ip.dst -e ip.dst_host -E header=y -E separator=,

      tvbuffer

       http://code.google.com/p/dns-mole/
      ```

  - mergecap
    ```
    # merge only same link layer
    mergecap -F libpcap -w all.pcap a.pcap b.pcap
    ```

  - epan(Etheral Packet Analyzer)

  - [configure in ubuntu](https://www.wireshark.org/docs/wsdg_html_chunked/index.html)
    ```
    # Get the development packages needed to build Wireshark
    apt-cache search libgcryp*
    apt-get install libgcrypt20 libgcrypt20-dbg libgcrypt20-dev
    
    sudo apt-get build-dep wireshark
    sudo apt-get install qt5-default
    sudo apt-get install libssl-dev
    sudo apt-get install libgtk-3-dev
    
    # build
    ./autogen.sh
    ./configure --with-ssl --enable-setcap-install

    - debug
      ```
      libtool --mode=execute gdb wireshark

      apt install ddd
      G_DEBUG=fatal_criticals libtool --mode=execute ddd wireshark
      ```

# [pf_ring](http://www.ntop.org/products/packet-capture/pf_ring/)
  - introduction
    - High-speed packet capture, filtering and analysis.
    - ZC(Zero Copy): no sk_buffer copy in libpcap, using mmap
    - DNA(Direct NIC Access)

# network config
  - ethtool
    ```
    ethtool -k eth1

    ethtool -K eth1 gso off tso off

    ifconfig eth1 mtu 9000
    ip link set eth1 mtu 9000

    netstat -i

    ping -s 40000 -M do eth1
    ```

- windows
  - [TCP Chimney Offload overview](https://support.microsoft.com/en-us/help/951037/information-about-the-tcp-chimney-offload--receive-side-scaling--and-n#LetMeFixItMyselfAlways)
    - TCP Chimney Offload is a networking technology that helps transfer the workload from the CPU to a network adapter during network data transfer. 
    ```
    netsh int tcp set global chimney=enabled
    netsh int tcp set global chimney=disabled
    netsh int tcp show global

    netstat –t
      Active Connections

        Proto  Local Address          Foreign Address        State           Offload State

        TCP    127.0.0.1:52613        computer_name:52614       ESTABLISHED     InHost
        TCP    192.168.1.103:52614        computer_name:52613       ESTABLISHED     Offloaded
 
    ```

    - Receive Side Scaling (RSS)
      ```
      netsh int tcp set global rss=enabled
      netsh int tcp set global rss=disabled
      netsh int tcp show global
      ```

    - Network Direct Memory Access (NetDMA) features
      ```
      HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Tcpip\Parameters

      EnableTCPA: DWORD Value
      enable NetDMA, type 1
      disable NetDMA, type 0
      ```

# OSI
  - SDU and PDU
  - TCP UDP SCTP DCCP NCP
  - SIP (Session Initial Protocol)
  - STUN (Session Traversal Utilities for NAT)

  - Kerberos
     - PAC stands for Privilege Attribute Certificate 

# codec
  - [ASN.1](http://www.itu.int/en/ITU-T/asn1/Pages/introduction.aspx)
    - BER(Basic Encoding Rules)
    - CER(Canonical Encoding Rules )
    - DER(Distinguished Encoding Rules )

# windows
  - [service port](https://support.microsoft.com/en-us/help/832017#method8)
    ```
    WSD (Web Service for Device)

    SSDP(Simple Service Discover Protocol)
    Get-NetFirewallRule -Name "*ssdp*" | Set-NetFirewallRule -Action Block
    ```

- winpcap
  - NPF(Netgroup Packet Filter)(https://www.winpcap.org/docs/docs_41b5/html/group__NPF.html)
    - NDIS and NPF
    - BPF

# todo
- http header print using tshark
- [network driver](https://stackoverflow.com/questions/7763321/libpcap-to-capture-10-gbps-nic)
  - [netmap](https://sgros-students.blogspot.jp/2013/12/netmap-and-pfring-dna.html)
    three major identified bottlenecks
    - per packet dynamic memory allocations: preallocation
    - system call overheads:  less system call with batches and not packets individually
    - memory copies: sharing buffers and metadata between kernel and userspace.

  - PF-RING(http://luca.ntop.org/Ring.pdf)
      - ZC:reveals NIC memory and registers to userland so that there is no additional packet copy.
      - drawback: only one application at time can have access to NIC memory and registers.

  - PF-RING+netmap
    - both Netmap and PF_RING is that they both bypass kernel completely:
      - packet processing in Netfilter is skipped and there is no NAT or packet filtering involved
        - PF_RING offers solution in Hardware Packet Filtering but the main problem still stands 
        - but TCP packet must be sent, control of those packet and TCP processing must be implemented in user-space
    
    - difference
      -  Netmap offers protected usage of NIC's memory and register while latter doesn't.
    OpenOnload
    DPDK
    PacketShader
