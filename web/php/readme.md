# install # 
    * with nginx: http://www.shaunfreeman.name/compiling-php-7-on-centos/
        sudo yum install git gcc gcc-c++ libxml2-devel pkgconfig openssl-devel bzip2-devel curl-devel libpng-devel libjpeg-devel libXpm-devel freetype-devel gmp-devel libmcrypt-devel mariadb-devel aspell-devel recode-devel autoconf bison re2c libicu-devel

        Once ‘International Components for Unicode’ is installed
        # ./buildconf --force
        ./configure --prefix=/usr/local/php \
        --with-config-file-path=/usr/local/php/etc \
        --with-config-file-scan-dir=/usr/local/php/etc/php.d \
        --enable-phpdbg \
        --enable-bcmath \
        --with-bz2 \
        --with-curl \
        --enable-filter \
        --enable-fpm \
        --with-fpm-user=nginx \
        --with-fpm-group=nginx \
        --with-gd \
        --enable-gd-native-ttf \
        --with-freetype-dir \
        --with-jpeg-dir \
        --with-png-dir \
        --enable-intl \
        --enable-mbstring \
        --with-mcrypt \
        --enable-mysqlnd \
        -with-mysql-sock=/opt/mysql/mysql.sock \
        --with-mysqli=mysqlnd \
        --with-pdo-mysql=mysqlnd \
        --with-sqlite3 \
        --with-pdo-sqlite \
        --with-pdo-pgsql \
        --with-pgsql \
        --disable-phpdbg \
        --disable-phpdbg-webhelper \
        --enable-opcache \
        --with-openssl \
        --with-pear \
        --enable-simplexml \
        --enable-soap  \
        --enable-xmlreader \
        --enable-xmlwriter \
        --enable-zip \
        --with-zlib
        make
        sudo make install

        vim /etc/man.config
        MANPATH /usr/local/php/php/man

        cp php.ini-development /usr/local/php/etc/php.ini
        cp /usr/local/php/etc/php-fpm.conf.default /usr/local/php/etc/php-fpm.conf
        # cp sapi/fpm/php-fpm /usr/local/php/bin



    vim /usr/local/php/etc/php.ini
    cgi.fix_pathinfo=0

    vim /usr/local/php/etc/php-fpm.conf
        PHP-FPM (FastCGI Process Manager) 

    ln -s /usr/local/php/sbin/php-fpm /usr/local/sbin/php-fpm

    /etc/profile.d/php.sh
    #!/bin/sh

    PHP_DIR=/usr/local/php
    export PATH=${php_dir}/bin:$PATH

    export PHPRC="${PHP_DIR}/etc/php.ini"
    export PHP_INI_SCAN_DIR="${PHP_DIR}/etc/php.d"



    vim /usr/local/nginx/conf/nginx.conf
        location ~* \.php$ {
            fastcgi_index   index.php;
            fastcgi_pass    127.0.0.1:9000;
            include         fastcgi_params;
            fastcgi_param   SCRIPT_FILENAME    $document_root$fastcgi_script_name;
            fastcgi_param   SCRIPT_NAME        $fastcgi_script_name;
        }

        rm /usr/local/nginx/html/index.html

    echo "<?php phpinfo(); ?>" >> /usr/local/nginx/html/index.php


    cp <php-5.3.3-source-dir>/sapi/fpm/init.d.php-fpm /etc/init.d/php-fpm
	$ chmod 755 /etc/init.d/php-fpm
	chkconfig --add php-fpm
	chkconfig --level 2345 php-fpm on

	php -m
	php --ini

	export PHPRC="/usr/local/php/php.ini"
	export PHP_INI_SCAN_DIR="/usr/local/php/php.d" 

* connect mysql
    $servername = "localhost";
    # $servername = "127.0.0.1";
    vim /usr/local/php/php.ini
        pdo_mysql.default_socket=/opt/mysql/mysql.sock
        mysqli.default_socket = /opt/mysql/mysql.sock


# php #
	* start php built-in server
		php -S 0.0.0.0:8099
	* comment
		# 
		/* */
	*  case sensitivity:
		1. all keywords (e.g. if, else, while, echo, etc.), classes, functions, and user-defined functions are NOT case-sensitive.
			ECHO "Hello World!<br>";
			echo "Hello World!<br>";
			EcHo "Hello World!<br>";

		2. all variable names are case-sensitive.

	* declaration
		$
		$a = "helloc"

	* scope 
		local : A variable declared within a function has a LOCAL SCOPE and can only be accessed within that function:

		global : A variable declared outside a function has a GLOBAL SCOPE and can only be accessed outside a function
			<?php
			$x = 5;
			$y = 10;

			function myTest() {
			    global $x, $y;
			    $y = $x + $y;
			}
			function myTest() {
				    $GLOBALS['y'] = $GLOBALS['x'] + $GLOBALS['y'];
				}

			myTest();
			echo $y; // outputs 15
			?> 

		static : local variable NOT to be deleted
			<?php
			function myTest() {
			    static $x = 0;
			    echo $x;
			    $x++;
			}

			myTest();
			myTest();
			myTest();
			?> 

		PHP Global Variables - Superglobals

		    $GLOBALS
		    $_SERVER
		    $_REQUEST
		    $_POST
		    $_GET
		    $_FILES
		    $_ENV
		    $_COOKIE
		    $_SESSION
		    	/%22%3E%3Cscript%3Ealert('hacked')%3C/script%3E
	*data types

	    String
	    Integer:
	    	An integer must have at least one digit
		    An integer must not have a decimal point
		    An integer can be either positive or negative
		    Integers can be specified in three formats: decimal (10-based), hexadecimal (16-based - prefixed with 0x) or octal (8-based - prefixed with 0)

		     filter_var() : filter_var($email, FILTER_VALIDATE_EMAIL)

	    Float (floating point numbers - also called double)
	    Boolean:
	    	$x = true;
			$y = false;
	    Array:
	    	$cars = array("Volvo","BMW","Toyota");

		    Indexed arrays - Arrays with a numeric index
		    Associative arrays - Arrays with named keys
		    	$age = array("Peter"=>"35", "Ben"=>"37", "Joe"=>"43");
		    Multidimensional arrays - Arrays containing one or more arrays
		    	<?php
				$age = array("Peter"=>"35", "Ben"=>"37", "Joe"=>"43");

				foreach($age as $x => $x_value) {
				    echo "Key=" . $x . ", Value=" . $x_value;
				    echo "<br>";
				}
				?> 

	    	<?php
			$cars = array("Volvo", "BMW", "Toyota");
			echo count($cars);
			?> 


		    sort() - sort arrays in ascending order
		    rsort() - sort arrays in descending order
		    asort() - sort associative arrays in ascending order, according to the value
		    ksort() - sort associative arrays in ascending order, according to the key
		    arsort() - sort associative arrays in descending order, according to the value
		    krsort() - sort associative arrays in descending order, according to the key


	    Object
	    NULL:
	    	A variable of data type NULL is a variable that has no value assigned to it.
	    	If a variable is created without a value, it is automatically assigned a value of NULL.
	    	Variables can also be emptied by setting the value to NULL:

	    Resource:
	    	storing of a reference to functions and resources external to PHP

	* constant: global
		define(name, value, case-insensitive)  # default case-insensitive
		 <?php
		define("GREETING", "Welcome to W3Schools.com!", true);
		echo greeting;
		?> 

	* operation
		== 	Equal
		=== 	Identical

		. 	Concatenation
		.= 	Concatenation assignment 	$txt1 .= $txt2

		++$x
		x += y

	* condition
		if (condition) {
		    code to be executed if this condition is true;
		} elseif (condition) {
		    code to be executed if this condition is true;
		} else {
		    code to be executed if all conditions are false;
		} 

		switch (n) {
		    case label1:
		        code to be executed if n=label1;
		        break;
		    case label2:
		        code to be executed if n=label2;
		        break;
		    case label3:
		        code to be executed if n=label3;
		        break;
		    ...
		    default:
		        code to be executed if n is different from all labels;
		} 

		loop:

		    while - loops through a block of code as long as the specified condition is true
		    do...while - loops through a block of code once, and then repeats the loop as long as the specified condition is true
		    for - loops through a block of code a specified number of times
		    foreach - loops through a block of code for each element in an array:
	    	 	<?php
				$colors = array("red", "green", "blue", "yellow");

				foreach ($colors as $value) {
				    echo "$value <br>";
				}
				?> 
	* function : not case-sensitive
		<?php
		function familyName($fname="default") {
		    echo "$fname Refsnes.<br>";
		}
		familyName();
		familyName("Jani");
		familyName("Hege");
		familyName("Stale");
		familyName("Kai Jim");
		familyName("Borge");
		?>

	* regex
		preg_match
		#!/usr/bin/perl 

		$string = 'the cat sat on the mat.';
		$string =~ tr/a-z/b/d;

		print "$string\n";

		This will produce following result
		b b   b.

		Since there is only one character in the replacement list (b), only the first character in the searchlist (a) will be replaced with b. The rest of characters in the search list (b-z) will be deleted.

		Hence, replacing as with bs and b-z letters with nothing,

		    the cat sat on the mat.

		becomes  b b   b

	* datetime
		date(format,timestamp) 

	    d - Represents the day of the month (01 to 31)
	    m - Represents a month (01 to 12)
	    Y - Represents a year (in four digits)
	    l (lowercase 'L') - Represents the day of the week

	    h - 12-hour format of an hour with leading zeros (01 to 12)
	    i - Minutes with leading zeros (00 to 59)
	    s - Seconds with leading zeros (00 to 59)
	    a - Lowercase Ante meridiem and Post meridiem (am or pm)

	    mktime(hour,minute,second,month,day,year) 

	    strtotime(time,now)

	    <?php
		$d=strtotime("10:30pm April 15 2014");
		echo "Created date is " . date("Y-m-d h:i:sa", $d);
		?>

	* include files
		
	    require will produce a fatal error (E_COMPILE_ERROR) and stop the script
	    include will only produce a warning (E_WARNING) and the script will continue
