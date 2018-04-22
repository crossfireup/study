# start up

[W3school Javascript](http://www.w3schools.com/js/)

[Learn javaScript free online](https://www.developphp.com/lib/JavaScript#Fundamentals)

[The Markdown Extended Package](https://donlelek.github.io/2015-03-25-how-to-use-markdown-and-pandoc-in-sublime-text-3/ "TITLE").

[Javascript resources](https://www.javascript.com/resources)

[JavaScript Language Reference](https://docs.microsoft.com/en-us/scripting/javascript/javascript-language-reference)
 libraries (like jQuery)
 
 frameworks (like AngularJS, ReactJS and NodeJS)

## js location

  * head
  * body
  * externalk
     __The script will behave as if it was located exactly where the \<script\> tag is located.__

     External scripts cannot contain \<script\> tags.
    1. It separates HTML and code
    2. It makes HTML and JavaScript easier to read and maintain
    3. Cached JavaScript files can speed up page loads

## output

  * JavaScript Display Possibilities
  
    JavaScript can "display" data in different ways:

    1. Writing into an alert box, using window.alert().
    2. Writing into the HTML output using document.write().
    3. Writing into an HTML element, using innerHTML.
    4. Writing into the browser console, using console.log().

## syntax ##
  * comment
  
    Code after double    slashes // or between /* and */ is treated as a comment.
  
  * Strings are text, written within double or single quotes:
      
    "John Doe"

    'John Doe' 
  
  * Numbers are written with or without decimals:
  
    10.50
  
    1001 
  
  * Identifiers are names:
  
    * In JavaScript, identifiers are used to name variables (and keywords, and functions, and labels).
    * The rules for legal names are much the same in most programming languages.
    * In JavaScript, the first character must be a letter, an underscore (_), or a dollar sign ($).
    * Subsequent characters may be letters, digits, underscores, or dollar signs.
  
  * case sensitivity
      
    JavaScript is Case Sensitive
  
    All JavaScript identifiers are __**case sensitive**__.
  
  * name conventions
  
    1. Hyphens:
      first-name, last-name, master-card, inter-city.
      Hyphens are not allowed in JavaScript. It is reserved for subtractions.
  
    2. Underscore:
  
      ```
      first_name, last_name, master_card, inter_city.
      ```
  
    3. Camel Case:
      
        FirstName, LastName, MasterCard, InterCity.
  
  * charset 
  
    JavaScript uses the Unicode character set.
  
  * keywords
  
    Keyword           |       Description
    --------------    |        --
    break             | Terminates a switch or a loop
    continue          | Jumps out of a loop and starts at the top
    debugger          | Stops the execution of JavaScript, and calls (if available) the debugging function
    do ... while      | Executes a block of statements, and repeats the block, while a condition is true
    for               | Marks a block of statements to be executed, as long as a condition is true
    function          | Declares a function
    if ... else       | Marks a block of statements to be executed, depending on a condition
    return            | Exits a function
    switch            | Marks a block of statements to be executed, depending on different cases
    try ... catch     | Implements error handling to a block of statements
    var               | Declares a variable
  
  * variable
  
    1. Value = undefined
  
       var carName; 
  
    2. Re-Declaring JavaScript Variables
  
        If you re-declare a JavaScript variable, it will not lose its value.
  
        __The variable carName will still have the value "Volvo" after the execution of these statements:__
  
    3. If you put a number in quotes, the rest of the numbers will be treated as strings, and concatenated.
   
      ```javascript
      var x = 2 + 3 + "5";
      The result of adding 2 + 3 + "5":
          55
      ```
  
  * operators
  
    1. alrithmatic
  
       ```
        ++  Increment
      
        --  Decrement
  
        +=  x += y  x = x + y
  
        -=  x -= y  x = x - y
       ```
  
    2. comparision
  
       operator |  description
       --       |  --
       ==       |  equal to
       ===      |  equal value and equal type
       !=       |  not equal
       !==      |  not equal value or not equal type
  
    3. type operators:
      
        operator   | description
        --------   | --
        typeof     | Returns the type of a variable
        instanceof | Returns true if an object is an instance of an object type
  
    4. Bitwise Operators
  
        Operator | Description | Example | Same as | Result | Decimal 
        ---------| -- | -- | -- | -- | --
        <<  | Zero fill left shift   |  x = 5 << 1  |  0101 << 1  | 1010 | 10
        >>  | Signed right shift     |  x = 5 >> 1  |  0101 >> 1  | 0010 |  2
        >>> | Zero fill right shift  |  x = 5 >>> 1 |  0101 >>> 1 | 0010 |  2

  * data types
    
    ```javascript
    var length = 16;                               // Number
    var lastName = "Johnson";                      // String
    var cars = ["Saab", "Volvo", "BMW"];           // Array
    var x = {firstName:"John", lastName:"Doe"};    // Object
    ```

    * string operator:
      ```javascript
      var x = "Volvo" + 16 + 4; 
      var x = "Volvo" + 16 + 4; 
      ```
    
    * boolean
      ```javascript
      var x = true;
      var y = false;
      ```
    
    * The typeof Operator
      ```javascript
      typeof "John"                // Returns "string"
      typeof 3.14                  // Returns "number"
      typeof false                 // Returns "boolean"
      typeof [1,2,3,4]             // Returns "object" (not "array", see note below)
      typeof {name:'John', age:34} // Returns "object" 
      ```
    
    * undefined

        In JavaScript, a variable without a value,
         has the value undefined. The typeof is also undefined.

         ```javascript
         var person;

         // or
         person = undefined;
         ```
    
    * Empty Values

      An empty value has nothing to do with undefined.

      An empty string variable has both a value and a type.

      ```javascript
      var car = "";  // car is empty of which type is string
      ```
    
    * Null

      In JavaScript null is "nothing". It is supposed to be something that doesn't exist.

      Unfortunately, in JavaScript, the data type of null is an object.

      ```javascript
      var person = null; //person is nothing but it's type is object
      ```
    
    * __comparison between null and undefined__
    
      ```javascript
      typeof undefined;   // undefined
      typeof null;        // object
      null == undefined;  // true
      null === undefined; // false
      ```

  * functions

    The code inside the function will execute when "something" invokes (calls) the function:
      * When an event occurs (when a user clicks a button)
      * When it is invoked (called) from JavaScript code
      * Automatically (self invoked)

  * object

    ```javascript
    var person = {
        firstName:"John",
        lastName:"Doe",
        age:50,
        eyeColor:"blue"
        fullName:function(){
            return this.firstName + ' ' + this.LastName;
        }
    }; 
    person.lastName; // Doe
    person.fullName(); // Johe Doe
    persson.fullName; 
    /*return function definetion:
        function(){
            return this.firstName + ' ' + this.LastName;
        }
    */
    ```

    If you access the fullName method, without (), it will return the function definition:

    __Do Not Declare Strings, Numbers, and Booleans as Objects!__

    **Avoid String, Number, and Boolean objects. They complicate your code and slow down execution speed.**

  * scope

    * global

      deleted when the function is completed.

      In HTML, the global scope is the window object. 
      All global variables belong to the window object.
        ```javascript
        var carName = "Volvo";

        // code here can use window.carName
        ```
        
      1. outside function:
        ```javascript
        var carName = " Volvo";

        // code here can use carName

        function myFunction() {

            // code here can use carName

        } 
        ```

      2. Automatically global:  

          inside function without a declaration  
          ```javascript
            myFunction();

            // code here can use carName

            function myFunction() {
                carName = "Volvo";
            }
          ```        
    * local

        deleted when the function is completed.

  * loop

    ```javascript
    for (x in person) {
        txt += person[x] + " ";
    }
    ```
    
  * event
    
    HTML Events

    An HTML event can be something the browser does, or something a user does.

    Here are some examples of HTML events:

      * An HTML web page has finished loading
      * An HTML input field was changed
      * An HTML button was clicked

    javaScript lets you execute code when events are detected.

    HTML allows event handler attributes, with JavaScript code, to be added to HTML elements.

    With single quotes:
    ```<some-HTML-element some-event='some JavaScript'>```

    With double quotes:
    ```<some-HTML-element some-event="some JavaScript">```

    * common html event

        Event |	Description
        - | -
        onchange |	An HTML element has been changed
        onclick  |	The user clicks an HTML element
        onmouseover |	The user moves the mouse over an HTML element
        onmouseout |	The user moves the mouse away from an HTML element
        onkeydown |	The user pushes a keyboard key
        onload 	| The browser has finished loading the page
    
  * string

    ```javascript
    var x = "John";             
    var y = new String("John");

    // (x === y) is false because x and y have different types (string and object) 


    var x = new String("John");             
    var y = new String("John");

    // (x == y) is false because x and y are different objects
    // (x == x) is true because both are the same object
    ```

  * number

    **JavaScript Numbers are Always 64-bit Floating Point**

        Value (aka Fraction/Mantissa) |	Exponent | Sign
        ----------------------------- | -------- | ---
        52 bits (0 - 51)  |	11 bits (52 - 62) |	1 bit (63)

    * precision

      Integers are considered accurate up to 15 digits.
      
      ```javascript
      var x = 999999999999999;   // x will be 999999999999999
      var y = 9999999999999999;  // y will be 10000000000000000 
      ```

      maximum number of decimals is __17__, 
      but floating point arithmetic is not always **100% accurate**:
      ```javascript
       var x = 0.2 + 0.1;         // x will be 0.30000000000000004
       ```
    
    * Infinity

      a number outside the largest possible number.
      ```javascript
      var x =  2 / 0;          // x will be Infinity
      var y = -2 / 0;          // y will be -Infinity
       
      typeof Infinity;        // returns "number"
      ```
    * NaN - Not a Number

        NaN is a JavaScript reserved word indicating that a number is not a legal number.
        ```javascript
        var x = 100 / "Apple";  // x will be NaN (Not a Number)
        isNaN(x);               // returns true because x is Not a Number 

        //However, if the string contains a numeric value , the result will be a number:
        var x = 100 / "10"; // x will be 10

        var x = NaN;
        var y = 5;
        var z = x + y;         // z will be NaN 

         typeof NaN;             // returns "number"
        ```
    
    * methods
      ```javascript
      var x = 123;
      x.toString();            // returns 123 from variable x
      (123).toString();        // returns 123 from literal 123
      (100 + 23).toString();   // returns 123 from expression 100 + 23 

      var x = 9.656;
      x.toExponential(2);     // returns 9.66e+0
      x.toExponential(4);     // returns 9.6560e+0
      x.toExponential(6);     // returns 9.656000e+0 

      var x = 9.656;
      x.toFixed(0);           // returns 10
      x.toFixed(2);           // returns 9.66
      x.toFixed(4);           // returns 9.6560
      x.toFixed(6);           // returns 9.656000 
      ```
      methods:

        Method       |  Description
        - | -
        Number()     |  Returns a number, converted from its argument.
        parseFloat() |  Parses its argument and returns a floating point number
        parseInt()   |  Parses its argument and returns an integer

      Property:

        Number             | Properties
        ---------------    | ----------
        Property           | Description
        MAX_VALUE          | Returns the largest number possible in JavaScript
        MIN_VALUE          | Returns the smallest number possible in JavaScript
        NEGATIVE_INFINITY  | Represents negative infinity (returned on overflow)
        NaN 	           | Represents a "Not-a-Number" value
        POSITIVE_INFINITY  | Represents infinity (returned on overflow)

  * libriry
    
    * math

        ```javascript
        Math.PI;
        Math.pow();
        Math.sqort();
        Math.round();
        Math.floor(); //Math.floor(4.7);    // returns 4 

        Math.random() always returns a number lower than 1.
        Math.floor(Math.random() * 101);     // returns a number between 0 and 100 
        
        // min (included) and max (excluded):
        function getRndInteger(min, max) {
            return Math.floor(Math.random() * (max - min) ) + min;
        } 
        ```
  * date
    new Date()
    new Date(milliseconds)
    new Date(dateString)
    new Date(year, month, day, hours, minutes, seconds, milliseconds) 
  
  * Boolean
    
    __Everything With a "Real" Value is True__

    __Everything Without a "Real" is False__
    ```javaScript
    var x = 0;
    Boolean(x);       // zero returns false 

    var x = -0;
    Boolean(x);       // zero returns false 

    var x;
    Boolean(x);       // undefined returns false 

    var x = null;
    Boolean(x);       // null returns false 
    
    var x = 10 / "H";
    Boolean(x);       // NaN returns false 
    ```

    Converting Booleans to Strings

    The global method String() can convert booleans to strings.
    ```javaScript
    String(false)        // returns "false"
    String(true)         // returns "true"
    ```

    The Boolean method toString() does the same.
    ```javascript
    false.toString()     // returns "false"
    true.toString()      // returns "true"
    ```

  * comparision
    When comparing a string with a number, JavaScript will convert the string to a number when doing the comparison. 
    An empty string converts to 0. 
    A non-numeric string converts to NaN which is always false.

      Case        | Value 
      ---------   | ----- 
      2 < 12 	  | true 	
      2 < "12" 	  | true 	
      2 < "John"  | false 	
      2 > "John"  |	false 	
      2 == "John" |	false 	
      "2" < "12"  |	false 	
      "2" > "12"  |	true 	
      "2" == "12" |	false
  
  * exceptions
    try {
        Block of code to try
    }
    catch(err) {
        Block of code to handle errors
    }
    finally {
        Block of code to be executed regardless of the try / catch result
    }

    Technically you can throw an exception (throw an error).

  * hoisting
    
    Hoisting is JavaScript's default behavior of moving all declarations to the top of the current scope (to the top of the current script or the current function).

    __JavaScript only hoists declarations, not initializations.__
    ```javaScript
    var x; // Declare x
    x = 5; // Assign 5 to x

    var x = 5; // Initialize x
    var y = 7; // Initialize y
    ```

    __Declare Your Variables At the Top !__

    ```javaScript
    <form action="javascript:;" onsubmit="myFunction(this)">
    ```

* http

  When the user submits a form (e.g., by activating a submit button), the user agent processes it as follows.

    * Step one: Identify the successful controls 
    * Step two: Build a form data set 

        A form data set is a sequence of control-name/current-value pairs constructed from successful controls
    
    * Step three: Encode the form data set 

        The form data set is then encoded according to the content type specified by the enctype attribute of the FORM element.

    * Step four: Submit the encoded form data set 

    * Finally, the encoded data is sent to the processing agent designated by the action attribute using the protocol specified by the method attribute.

  This specification does not specify all valid submission methods or content types that may be used with forms. However, HTML 4 user agents must support the established conventions in the following cases:

    * If the method is "get" and the action is an HTTP URI, the user agent takes the value of action, appends a `?' to it, then appends the form data set, encoded using the "application/x-www-form-urlencoded" content type. The user agent then traverses the link to this URI. In this scenario, form data are restricted to ASCII codes.
    
    * If the method is "post" and the action is an HTTP URI, the user agent conducts an HTTP "post" transaction using the value of the action attribute and a message created according to the content type specified by the enctype attribute.

    For any other value of action or method, behavior is unspecified.

    User agents should render the response from the HTTP "get" and "post" transactions.


