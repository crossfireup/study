# exeption #
    * After closing and deleting the file, we call raise with no parameters, which reraises the exception in $!. 

    `f = File.open("testfile")
    begin
        # .. process
    rescue
        # .. handle error
        retry if # some conditon
    else
        puts "Congratulations-- no errors!"
    ensure
        f.close unless f.nil?
    end`

    catch (:done)  do
        while gets
            throw :done unless fields = split(/\t/)
            songList.add(Song.new(*fields))
        end
        songList.play
    end

# quoto #
    * %q()

# times #
    * 3.times {|x| puts "this is #{x}"}

# string #
    * "aBcD".swapcase

    * string = [<<ONE, <<TWO, <<THREE]
        the first thing
        ONE
        the second thing
        TWO
        and the third thing
        THREE
        => ["the first thing\n", "the second thing\n", "and the third
        thing\n"]

# number #
    * 5.step(50,5) {|x| puts "number is #{x}"}

# array
    myArray=%w(John Michel Fran Doug) # %w() can be used as syntactic    
    var1,var2,var3,var4= * myArray

    ["2", "3", "4"].inject("0"){|sum, elem| sum + elem}
    "0234"

# scope
    * local variable
        def l
            l_a
        end
        puts l_a # error
    * global $variable
        def g
            $g_a = 4
        end
        put $g_a
    * instance @variable
        class i
            def a(i_a)
                @i_a = i_a
            end
        end
    * class @@variable
        class c
            @@c_a = "class scope"

            def a(c_a)
                @@c_a = c_a
            end
        end
    *  Default scope    main
        default scope, which is an object called "main".
        @a = 33
        require 'other_script.rb'
        other_script.rb says
            puts @a
            #=> 33
        don't share local variables
    
# function #
    * results = method_name parameter1, parameter2 # calling method, not using parentheses
      You need to use parentheses if you want to work with the result immediately.
      e.g., if a method returns an array and we want to reverse element order:
        results = method_name(parameter1, parameter2).reverse

    * Methods return the value of the last statement executed. 
# proc lambda #
    * The ampersand (&)
        The ampersand operator can be used to explicitly convert between blocks and Procs in a couple of
        cases. It is worthy to understand how these work.
        def contrived(a, &f)
            # the block can be accessed through f
            f.call(a)
            # but yield also works !
            yield(a)
        end
        # this works
        contrived(25) {|x| puts x}
        # this raises ArgumentError, because &f
        # isn't really an argument - it's only there
        # to convert a block
        contrived(25, lambda {|x| puts x})
# class #
    * Accessor Methods:
        class MyClass
            def initialize
                @foo = 28
            end
            def foo
                return @foo
            end
            def foo=(value)
                @foo = value
            end
        end
        instance = MyClass.new
        puts instance.foo
        instance.foo = 496
        puts instance.foo


        class MyClass
            attr_accessor :foo
            def initialize
                @foo = 28
            end
        end
        instance = MyClass.new
        puts instance.foo
        instance.foo = 496
        puts instance.foo
    * class method
     class Example
        def instance_method # instance method
        end

        def Example.class_method # class method
        end
      end

      class Demo
        def Demo.meth1
            # ...
        end
        def self.meth2
            # ...
        end
        class <<self
            def meth3
                # ...
            end
        end
     end

   * private class method
    class MyLogger
        private_class_method :new
        @@logger = nil
        def MyLogger.create
            @@logger = new unless @@logger
            @@logger
        end
    end


    class MyClass
        def method1 # default is 'public'
            #...
        end

        protected # subsequent methods will be 'protected'
            def method2 # will be 'protected'
                #...
            end

        private # subsequent methods will be 'private'
            def method3 # will be 'private'
                #...
            end

        public # subsequent methods will be 'public'
            def method4 # and this will be 'public'
                #...
            end
    end

    class MyClass
        def method1
        end
        # ... and so on
        public :method1, :method4
        protected :method2
        private :method3
    end
# module #
     If that module is in a separate file, you must use require (or its less commonly used cousin, load ) to drag that file in before using include
     require '/usr/lib/ruby/1.9/English.rb'
     require '/usr/lib/ruby/1.9/rdoc/../English.rb'
     Ruby keeps a list of the files loaded by require in the array $"
        $" → ["/usr/lib/ruby/1.9/English.rb", "/usr/lib/ruby/1.9/rdoc/../English.rb"]

     The load method includes the named Ruby source file every time the method is executed.
        load 'filename.rb'
    The more commonly used require method loads any given file only once. 2
        require 'filename'
    
    Local variables in a loaded or required file are not propagatedto the scope that loads or requires them.

# cmdline #
    irb -r irb/completion

    ** vim ~/.irb
        require 'irb/completion'
    ** Initialization File
        following sources in order: ~/.irbrc , .irbrc , irb.rc , _irbrc , and $irbrc .

# package dependency #
    require 'rubygems'
    require_gem 'BlueCloth', '>= 0.0.5'


    gem install 
    Basicaly, you download the latest certificate https://raw.githubusercontent.com/rubygems/rubygems/master/lib/rubygems/ssl_certs/rubygems.org/AddTrustExternalCARoot.pem
        and place it in $RUBYHOME/lib/ruby/2.1.0/rubygems/ssl_certs. C:\Ruby23-x64\lib\ruby\2.3.0\rubygems\ssl_certs
    (Note that you might have a different version of rubygems installed than 2.1.0, so adjust the path appropriately).

    Rubygems should be using the certificate the next time you call the gem command.

    Step 1: Obtain the new trust certificate

        If you’ve read the previous sections, you will know what this means (and shame on you if you have not).

        We need to download GlobalSignRootCA.pem.

        Use the above link and place/save this file somewhere you can later find easily (eg. your Desktop).

        IMPORTANT: File must have .pem as extension. Browsers like Chrome will try to save it as plain text file. Ensure you change the filename to have .pem in it after you have downloaded it.
    Step 2: Locate RubyGems certificate directory in your installation

        In order for us copy this file, we need to know where to put it.

        Depending on where you installed Ruby, the directory will be different.

        Take for example the default installation of Ruby 2.1.5, placed in C:\Ruby21

        Open a Command Prompt and type in:

        C:\>gem which rubygems
        C:/Ruby21/lib/ruby/2.1.0/rubygems.rb

    Now, let’s locate that directory. From within the same window, enter the path part up to the file extension, but using backslashes instead:

        C:\>start C:\Ruby21\lib\ruby\2.1.0\rubygems

        This will open a Explorer window inside the directory we indicated.
        Step 3: Copy new trust certificate

        Now, locate ssl_certs directory and copy the .pem file we obtained from previous step inside.

        It will be listed with other files like AddTrustExternalCARoot.pem..
    Step 4: Profit

        There is actually no step 4. You should be able to install Ruby gems without issues now.

     def unsigned name, len, *rest
        opts = parse_options(rest, name, UnsignedField)
        add_field(name, len, opts)
     end

# operator #
    ..	Creates a range from start point to end point inclusive	: 1..10 Creates a range from 1 to 10 inclusive
    ...	Creates a range from start point to end point exclusive	: 1...10 Creates a range from 1 to 9