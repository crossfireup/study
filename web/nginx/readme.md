# install #
    * the PCRE library – required by NGINX Core and Rewrite modules and provides support for regular expressions:
        $ wget ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/pcre-8.39.tar.gz
        $ tar -zxf pcre-8.39.tar.gz
        $ cd pcre-8.39
        $ ./configure
        $ make
        $ sudo make install
    * the zlib library – required by NGINX Gzip module for headers compression:
        $ wget http://zlib.net/zlib-1.2.8.tar.gz
        $ tar -zxf zlib-1.2.8.tar.gz
        $ cd zlib-1.2.8
        $ ./configure
        $ make
        $ sudo make install

    * the OpenSSL library – required by NGINX SSL modules to support the HTTPS protocol:

        $ wget http://www.openssl.org/source/openssl-1.0.2f.tar.gz
        $ tar -zxf openssl-1.0.2f.tar.gz
        $ cd openssl-1.0.2f
        $ ./configure darwin64-x86_64-cc --prefix=/usr
        $ make
        $ sudo make install

    * To download and unpack source files for the latest mainline version, type-in the commands:
        $ wget http://nginx.org/download/nginx-1.11.6.tar.gz
        $ tar zxf nginx-1.11.6.tar.gz
        $ cd nginx-1.11.6
        $ ./configure \
    --prefix=/etc/nginx \
    --sbin-path=/usr/sbin/nginx \
    --conf-path=/etc/nginx/nginx.conf \
    --error-log-path=/var/log/nginx/error.log \
    --http-log-path=/var/log/nginx/access.log \
    --pid-path=/var/run/nginx.pid \
    --lock-path=/var/run/nginx.lock \
    --http-client-body-temp-path=/var/cache/nginx/client_temp \
    --http-proxy-temp-path=/var/cache/nginx/proxy_temp \
    --http-fastcgi-temp-path=/var/cache/nginx/fastcgi_temp \
    --http-uwsgi-temp-path=/var/cache/nginx/uwsgi_temp \
    --http-scgi-temp-path=/var/cache/nginx/scgi_temp \
    --user=nginx \
    --group=nginx \
    --with-http_ssl_module \
    --with-http_realip_module \
    --with-http_addition_module \
    --with-http_sub_module \
    --with-http_dav_module \
    --with-http_flv_module \
    --with-http_mp4_module \
    --with-http_gunzip_module \
    --with-http_gzip_static_module \
    --with-http_random_index_module \
    --with-http_secure_link_module \
    --with-http_stub_status_module \
    --with-http_auth_request_module \
    --with-threads \
    --with-stream \
    --with-stream_ssl_module \
    --with-http_slice_module \
    --with-mail \
    --with-mail_ssl_module \
    --with-file-aio \
    --with-http_v2_module \
    --with-ipv6 \
    --with-pcre=../pcre-8.39
    

Packages for mainline version also have the following arguments:

    --with-stream_realip_module

nginx config:
    ```
    groupadd nginx 
    useradd  nginx -g nginx

    init shell:
    #!/bin/sh
    #
    # nginx - this script starts and stops the nginx daemin
    #
    # chkconfig:   - 85 15
    # description:  Nginx is an HTTP(S) server, HTTP(S) reverse \
    #               proxy and IMAP/POP3 proxy server
    # processname: nginx
    # config:      /etc/nginx/nginx.conf
    # pidfile:     /var/run/nginx.pid
    # user:        nginx

    # Source function library.
    . /etc/rc.d/init.d/functions

    # Source networking configuration.
    . /etc/sysconfig/network

    # Check that networking is up.
    [ "$NETWORKING" = "no" ] && exit 0

    nginx="/usr/sbin/nginx"
    prog=$(basename $nginx)

    NGINX_CONF_FILE="/etc/nginx/nginx.conf"

    lockfile=/var/run/nginx.lock

    start() {
        [ -x $nginx ] || exit 5
        [ -f $NGINX_CONF_FILE ] || exit 6
        echo -n $"Starting $prog: "
        daemon $nginx -c $NGINX_CONF_FILE
        retval=$?
        echo
        [ $retval -eq 0 ] && touch $lockfile
        return $retval
    }

    stop() {
        echo -n $"Stopping $prog: "
        killproc $prog -QUIT
        retval=$?
        echo
        [ $retval -eq 0 ] && rm -f $lockfile
        return $retval
    }

    restart() {
        configtest || return $?
        stop
        start
    }

    reload() {
        configtest || return $?
        echo -n $"Reloading $prog: "
        killproc $nginx -HUP
        RETVAL=$?
        echo
    }

    force_reload() {
        restart
    }

    configtest() {
    $nginx -t -c $NGINX_CONF_FILE
    }

    rh_status() {
        status $prog
    }

    rh_status_q() {
        rh_status >/dev/null 2>&1
    }

    case "$1" in
        start)
            rh_status_q && exit 0
            $1
            ;;
        stop)
            rh_status_q || exit 0
            $1
            ;;
        restart|configtest)
            $1
            ;;
        reload)
            rh_status_q || exit 7
            $1
            ;;
        force-reload)
            force_reload
            ;;
        status)
            rh_status
            ;;
        condrestart|try-restart)
            rh_status_q || exit 0
                ;;
        *)
            echo $"Usage: $0 {start|stop|status|restart|condrestart|try-restart|reload|force-reload|configtest}"
            exit 2
    esac

    chmod +x /etc/init.d/nginx

    chkconfig --add nginx
    chkconfig --level 345 nginx on

    service nginx start 

    iptables -t filter -I INPUT -p tcp --dport 80 -j ACCEPT
    iptables -t filter -L INPUT --line-numbers
    iptables-save

    rpm -ql pcre
    ```

   * configure ssl for nginx server
    * openssl 
      ```
      https://www.nginx.com/blog/nginx-https-101-ssl-basics-getting-started/
      http://nginx.org/en/docs/http/ngx_http_ssl_module.html#ssl_protocols
      https://www.digitalocean.com/community/tutorials/how-to-create-an-ssl-certificate-on-nginx-for-ubuntu-14-04

      openssl req -x509 -nodes -days 366 -newkey rsa:2048 -keyout /etc/nginx/ssl/nginx.key -out /etc/nginx/ssl/nginx.cert
      Generating a 2048 bit RSA private key
      ..........+++
      .......................+++
      writing new private key to '/etc/nginx/ssl/nginx.key'
      -----
      You are about to be asked to enter information that will be incorporated
      into your certificate request.
      What you are about to enter is what is called a Distinguished Name or a DN.
      There are quite a few fields but you can leave some blank
      For some fields there will be a default value,
      If you enter '.', the field will be left blank.
      -----
      Country Name (2 letter code) [XX]:US
      State or Province Name (full name) []:New York 
      Locality Name (eg, city) [Default City]:New York City
      Organization Name (eg, company) [Default Company Ltd]:Dobly, Inc.
      Organizational Unit Name (eg, section) []:Security Department
      Common Name (eg, your name or your server's hostname) []:centos.dob.com
      Email Address []:doblys@yahoo.com

      iptables -t filter -I INPUT -p tcp --dport 443 -j ACCEPT
      service iptables save

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