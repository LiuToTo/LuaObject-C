//
//  LOLuaValue.h
//  Expecta
//
//  Created by 刘旭 on 2018/12/19.
//

#import "LOVarargs.h"

@class LOLuaNil;

/**
 * Base class for all concrete lua type values.
 * <p>
 * Establishes base implementations for all the operations on lua types.
 * This allows Java clients to deal essentially with one type for all Java values, namely {@link LuaValue}.
 * <p>
 * Constructors are provided as static methods for common Java types, such as
 * {@link LuaValue#valueOf(int)} or {@link LuaValue#valueOf(String)}
 * to allow for instance pooling.
 * <p>
 * Constants are defined for the lua values
 * {@link #NIL}, {@link #TRUE}, and {@link #FALSE}.
 * A constant {@link #NONE} is defined which is a {@link Varargs} list having no values.
 * <p>
 * Operations are performed on values directly via their Java methods.
 * For example, the following code divides two numbers:
 * <pre> {@code
 * LuaValue a = LuaValue.valueOf( 5 );
 * LuaValue b = LuaValue.valueOf( 4 );
 * LuaValue c = a.div(b);
 * } </pre>
 * Note that in this example, c will be a {@link LuaDouble}, but would be a {@link LuaInteger}
 * if the value of a were changed to 8, say.
 * In general the value of c in practice will vary depending on both the types and values of a and b
 * as well as any metatable/metatag processing that occurs.
 * <p>
 * Field access and function calls are similar, with common overloads to simplify Java usage:
 * <pre> {@code
 * LuaValue globals = JsePlatform.standardGlobals();
 * LuaValue sqrt = globals.get("math").get("sqrt");
 * LuaValue print = globals.get("print");
 * LuaValue d = sqrt.call( a );
 * print.call( LuaValue.valueOf("sqrt(5):"), a );
 * } </pre>
 * <p>
 * To supply variable arguments or get multiple return values, use
 * {@link #invoke(Varargs)} or {@link #invokemethod(LuaValue, Varargs)} methods:
 * <pre> {@code
 * LuaValue modf = globals.get("math").get("modf");
 * Varargs r = modf.invoke( d );
 * print.call( r.arg(1), r.arg(2) );
 * } </pre>
 * <p>
 * To load and run a script, {@link LoadState} is used:
 * <pre> {@code
 * LoadState.load( new FileInputStream("main.lua"), "main.lua", globals ).call();
 * } </pre>
 * <p>
 * although {@code require} could also be used:
 * <pre> {@code
 * globals.get("require").call(LuaValue.valueOf("main"));
 * } </pre>
 * For this to work the file must be in the current directory, or in the class path,
 * dependening on the platform.
 * See {@link org.luaj.vm2.lib.jse.JsePlatform} and {@link org.luaj.vm2.lib.jme.JmePlatform} for details.
 * <p>
 * In general a {@link LuaError} may be thrown on any operation when the
 * types supplied to any operation are illegal from a lua perspective.
 * Examples could be attempting to concatenate a NIL value, or attempting arithmetic
 * on values that are not number.
 * <p>
 * There are several methods for preinitializing tables, such as:
 * <ul>
 * <li>{@link #listOf(LuaValue[])} for unnamed elements</li>
 * <li>{@link #tableOf(LuaValue[])} for named elements</li>
 * <li>{@link #tableOf(LuaValue[], LuaValue[], Varargs)} for mixtures</li>
 * </ul>
 * <p>
 * Predefined constants exist for the standard lua type constants
 * {@link #TNIL}, {@link #TBOOLEAN}, {@link #TLIGHTUSERDATA}, {@link #TNUMBER}, {@link #TSTRING},
 * {@link #TTABLE}, {@link #TFUNCTION}, {@link #TUSERDATA}, {@link #TTHREAD},
 * and extended lua type constants
 * {@link #TINT}, {@link #TNONE}, {@link #TVALUE}
 * <p>
 * Predefined constants exist for all strings used as metatags:
 * {@link #INDEX}, {@link #NEWINDEX}, {@link #CALL}, {@link #MODE}, {@link #METATABLE},
 * {@link #ADD}, {@link #SUB}, {@link #DIV}, {@link #MUL}, {@link #POW},
 * {@link #MOD}, {@link #UNM}, {@link #LEN}, {@link #EQ}, {@link #LT},
 * {@link #LE}, {@link #TOSTRING}, and {@link #CONCAT}.
 *
 * @see org.luaj.vm2.lib.jse.JsePlatform
 * @see org.luaj.vm2.lib.jme.JmePlatform
 * @see LoadState
 * @see Varargs
 */
@interface LOLuaValue : LOVarargs

/** LuaValue constant corresponding to lua {@code #NIL} */
+ (LOLuaValue *)NIL;
+ (LOLuaValue *)NONE;

// type
/** Get the enumeration value for the type of this value.
 * @return value for this type, one of
 * {@link #TNIL},
 * {@link #TBOOLEAN},
 * {@link #TNUMBER},
 * {@link #TSTRING},
 * {@link #TTABLE},
 * {@link #TFUNCTION},
 * {@link #TUSERDATA},
 * {@link #TTHREAD}
 * @see #typename()
 */
- (int)type;

/** Get the String name of the type of this value.
 * <p>
 *
 * @return name from type name list {@link #TYPE_NAMES}
 * corresponding to the type of this value:
 * "nil", "boolean", "number", "string",
 * "table", "function", "userdata", "thread"
 * @see #type()
 */
- (NSString *)typeName;

/** Check if {@code this} is a {@code boolean}
 * @return true if this is a {@code boolean}, otherwise false
 * @see #isboolean()
 * @see #toboolean()
 * @see #checkboolean()
 * @see #optboolean(boolean)
 * @see #TBOOLEAN
 */
- (BOOL)isBoolean;

/** Check if {@code this} is a {@code function} that is a closure,
 * meaning interprets lua bytecode for its execution
 * @return true if this is a {@code closure}, otherwise false
 * @see #isfunction()
 * @see #checkclosure()
 * @see #optclosure(LuaClosure)
 * @see #TFUNCTION
 */
- (BOOL)isClosure;

/** Check if {@code this} is a {@code function}
 * @return true if this is a {@code function}, otherwise false
 * @see #isclosure()
 * @see #checkfunction()
 * @see #optfunction(LuaFunction)
 * @see #TFUNCTION
 */
- (BOOL)isFunction;

/** Check if {@code this} is a {@code number} and is representable by java int
 * without rounding or truncation
 * @return true if this is a {@code number}
 * meaning derives from {@link LuaNumber}
 * or derives from {@link LuaString} and is convertible to a number,
 * and can be represented by int,
 * otherwise false
 * @see #isinttype()
 * @see #islong()
 * @see #tonumber()
 * @see #checkint()
 * @see #optint(int)
 * @see #TNUMBER
 */
- (BOOL)isInt;

/** Check if {@code this} is a {@link LuaInteger}
 * <p>
 * No attempt to convert from string will be made by this call.
 * @return true if this is a {@code LuaInteger},
 * otherwise false
 * @see #isint()
 * @see #isnumber()
 * @see #tonumber()
 * @see #TNUMBER
 */
- (BOOL)isIntType;

/** Check if {@code this} is a {@code number} and is representable by java long
 * without rounding or truncation
 * @return true if this is a {@code number}
 * meaning derives from {@link LuaNumber}
 * or derives from {@link LuaString} and is convertible to a number,
 * and can be represented by long,
 * otherwise false
 * @see #tonumber()
 * @see #checklong()
 * @see #optlong(long)
 * @see #TNUMBER
 */
- (BOOL)isLong;

/** Check if {@code this} is {@code #NIL}
 * @return true if this is {@code #NIL}, otherwise false
 * @see #NIL
 * @see #NONE
 * @see #checknotnil()
 * @see #optvalue(LuaValue)
 * @see Varargs#isnoneornil(int)
 * @see #TNIL
 * @see #TNONE
 */
- (BOOL)isNil;

/** Check if {@code this} is a {@code number}
 * @return true if this is a {@code number},
 * meaning derives from {@link LuaNumber}
 * or derives from {@link LuaString} and is convertible to a number,
 * otherwise false
 * @see #tonumber()
 * @see #checknumber()
 * @see #optnumber(LuaNumber)
 * @see #TNUMBER
 */
- (BOOL)isNumber;

/** Check if {@code this} is a {@code string}
 * @return true if this is a {@code string},
 * meaning derives from {@link LuaString} or {@link LuaNumber},
 * otherwise false
 * @see #tostring()
 * @see #checkstring()
 * @see #optstring(LuaString)
 * @see #TSTRING
 */
- (BOOL)isString;

/** Check if {@code this} is a {@code thread}
 * @return true if this is a {@code thread}, otherwise false
 * @see #checkthread()
 * @see #optthread(LuaThread)
 * @see #TTHREAD
 */
- (BOOL)isThread;

/** Check if {@code this} is a {@code table}
 * @return true if this is a {@code table}, otherwise false
 * @see #checktable()
 * @see #opttable(LuaTable)
 * @see #TTABLE
 */
- (BOOL)isTable;

/** Check if {@code this} is a {@code userdata}
 * @return true if this is a {@code userdata}, otherwise false
 * @see #isuserdata(Class)
 * @see #touserdata()
 * @see #checkuserdata()
 * @see #optuserdata(Object)
 * @see #TUSERDATA
 */
- (BOOL)isUserData;

/** Check if {@code this} is a {@code userdata} of type {@code c}
 * @param c Class to test instance against
 * @return true if this is a {@code userdata}
 * and the instance is assignable to {@code c},
 * otherwise false
 * @see #isuserdata()
 * @see #touserdata(Class)
 * @see #checkuserdata(Class)
 * @see #optuserdata(Class, Object)
 * @see #TUSERDATA
 */
- (BOOL)isUserData:(Class)c;

/** Convert to boolean false if {@link #NIL} or {@link #FALSE}, true if anything else
 * @return Value cast to byte if number or string convertible to number, otherwise 0
 * @see #optboolean(boolean)
 * @see #checkboolean()
 * @see #isboolean()
 * @see #TBOOLEAN
 */
- (BOOL)toBoolean;

/** Convert to byte if numeric, or 0 if not.
 * @return Value cast to byte if number or string convertible to number, otherwise 0
 * @see #toint()
 * @see #todouble()
 * @see #checknumber()
 * @see #isnumber()
 * @see #TNUMBER
 */
- (Byte)toByte;

/** Convert to char if numeric, or 0 if not.
 * @return Value cast to char if number or string convertible to number, otherwise 0
 * @see #toint()
 * @see #todouble()
 * @see #checknumber()
 * @see #isnumber()
 * @see #TNUMBER
 */
- (char)toChar;

/** Convert to double if numeric, or 0 if not.
 * @return Value cast to double if number or string convertible to number, otherwise 0
 * @see #toint()
 * @see #tobyte()
 * @see #tochar()
 * @see #toshort()
 * @see #tolong()
 * @see #tofloat()
 * @see #optdouble(double)
 * @see #checknumber()
 * @see #isnumber()
 * @see #TNUMBER
 */
- (double)toDouble;

/** Convert to float if numeric, or 0 if not.
 * @return Value cast to float if number or string convertible to number, otherwise 0
 * @see #toint()
 * @see #todouble()
 * @see #checknumber()
 * @see #isnumber()
 * @see #TNUMBER
 */
- (float)toFloat;

/** Convert to int if numeric, or 0 if not.
 * @return Value cast to int if number or string convertible to number, otherwise 0
 * @see #tobyte()
 * @see #tochar()
 * @see #toshort()
 * @see #tolong()
 * @see #tofloat()
 * @see #todouble()
 * @see #optint(int)
 * @see #checknumber()
 * @see #isnumber()
 * @see #TNUMBER
 */
- (int)toInt;

/** Convert to long if numeric, or 0 if not.
 * @return Value cast to long if number or string convertible to number, otherwise 0
 * @see #isint()
 * @see #isinttype()
 * @see #toint()
 * @see #todouble()
 * @see #optlong(long)
 * @see #checknumber()
 * @see #isnumber()
 * @see #TNUMBER
 */
- (long)toLong;

/** Convert to short if numeric, or 0 if not.
 * @return Value cast to short if number or string convertible to number, otherwise 0
 * @see #toint()
 * @see #todouble()
 * @see #checknumber()
 * @see #isnumber()
 * @see #TNUMBER
 */
- (short)toShort;

/** Convert to human readable String for any type.
 * @return String for use by human readers based on type.
 * @see #tostring()
 * @see #optjstring(String)
 * @see #checkjstring()
 * @see #isstring()
 * @see #TSTRING
 */
- (NSString *)toNSString;

/** Convert to userdata instance, or null.
 * @return userdata instance if userdata, or null if not {@link LuaUserdata}
 * @see #optuserdata(Object)
 * @see #checkuserdata()
 * @see #isuserdata()
 * @see #TUSERDATA
 */
- (id)toUserData;

/** Convert to userdata instance if specific type, or null.
 * @return userdata instance if is a userdata whose instance derives from {@code c},
 * or null if not {@link LuaUserdata}
 * @see #optuserdata(Class,Object)
 * @see #checkuserdata(Class)
 * @see #isuserdata(Class)
 * @see #TUSERDATA
 */
- (id)toUserData:(Class)c;

/**
 * Convert the value to a human readable string using {@link #tojstring()}
 * @return String value intended to be human readible.
 * @see #tostring()
 * @see #tojstring()
 * @see #optstring(LuaString)
 * @see #checkstring()
 * @see #toString()
 */
- (NSString *)toString;

/** Conditionally convert to lua number without throwing errors.
 * <p>
 * In lua all numbers are strings, but not all strings are numbers.
 * This function will return
 * the {@link LuaValue} {@code this} if it is a number
 * or a string convertible to a number,
 * and {@link #NIL} for all other cases.
 * <p>
 * This allows values to be tested for their "numeric-ness" without
 * the penalty of throwing exceptions,
 * nor the cost of converting the type and creating storage for it.
 * @return {@code this} if it is a {@link LuaNumber}
 * or {@link LuaString} that can be converted to a number,
 * otherwise {@link #NIL}
 * @see #tostring()
 * @see #optnumber(LuaNumber)
 * @see #checknumber()
 * @see #toint()
 * @see #todouble()
 */
- (LOLuaNumber *)toNumber;

/** Conditionally convert to lua string without throwing errors.
 * <p>
 * In lua all numbers are strings, so this function will return
 * the {@link LuaValue} {@code this} if it is a string or number,
 * and {@link #NIL} for all other cases.
 * <p>
 * This allows values to be tested for their "string-ness" without
 * the penalty of throwing exceptions.
 * @return {@code this} if it is a {@link LuaString} or {@link LuaNumber},
 * otherwise {@link #NIL}
 * @see #tonumber()
 * @see #tojstring()
 * @see #optstring(LuaString)
 * @see #checkstring()
 * @see #toString()
 */
- (LOLuaValue *)toValueString;

/** Check that optional argument is a boolean and return its boolean value
 * @param defval boolean value to return if {@code this} is nil or none
 * @return {@code this} cast to boolean if a {@link LuaBoolean},
 * {@code defval} if nil or none,
 * throws {@link LuaError} otherwise
 * @throws LuaError if was not a boolean or nil or none.
 * @see #checkboolean()
 * @see #isboolean()
 * @see #TBOOLEAN
 */
- (BOOL)optBoolean:(BOOL)defval;

/** Check that optional argument is a closure and return as {@link LuaClosure}
 * <p>
 * A {@link LuaClosure} is a {@link LuaFunction} that executes lua byteccode.
 * @param defval {@link LuaClosure} to return if {@code this} is nil or none
 * @return {@code this} cast to {@link LuaClosure} if a function,
 * {@code defval} if nil or none,
 * throws {@link LuaError} otherwise
 * @throws LuaError if was not a closure or nil or none.
 * @see #checkclosure()
 * @see #isclosure()
 * @see #TFUNCTION
 */
- (LOLuaClosure *)optClosure:(LOLuaClosure *)defval;

/** Check that optional argument is a number or string convertible to number and return as double
 * @param defval double to return if {@code this} is nil or none
 * @return {@code this} cast to double if numeric,
 * {@code defval} if nil or none,
 * throws {@link LuaError} otherwise
 * @throws LuaError if was not numeric or nil or none.
 * @see #optint(int)
 * @see #optinteger(LuaInteger)
 * @see #checkdouble()
 * @see #todouble()
 * @see #tonumber()
 * @see #isnumber()
 * @see #TNUMBER
 */
- (double)optDouble:(double)defval;

/** Check that optional argument is a function and return as {@link LuaFunction}
 * <p>
 * A {@link LuaFunction} may either be a function that implements
 * functionality directly in Object-C,  or a {@link LuaClosure}
 * which is a {@link LuaFunction} that executes lua bytecode.
 * @param defval {@link LuaFunction} to return if {@code this} is nil or none
 * @return {@code this} cast to {@link LuaFunction} if a function,
 * {@code defval} if nil or none,
 * throws {@link LuaError} otherwise
 * @throws LuaError if was not a function or nil or none.
 * @see #checkfunction()
 * @see #isfunction()
 * @see #TFUNCTION
 */
- (LOLuaFunction *)optFunction:(LOLuaFunction *)defval;

/** Check that optional argument is a number or string convertible to number and return as int
 * @param defval int to return if {@code this} is nil or none
 * @return {@code this} cast to int if numeric,
 * {@code defval} if nil or none,
 * throws {@link LuaError} otherwise
 * @throws LuaError if was not numeric or nil or none.
 * @see #optdouble(double)
 * @see #optlong(long)
 * @see #optinteger(LuaInteger)
 * @see #checkint()
 * @see #toint()
 * @see #tonumber()
 * @see #isnumber()
 * @see #TNUMBER
 */
- (int)optInt:(int)defval;

/** Check that optional argument is a number or string convertible to number and return as {@link LuaInteger}
 * @param defval {@link LuaInteger} to return if {@code this} is nil or none
 * @return {@code this} converted and wrapped in {@link LuaInteger} if numeric,
 * {@code defval} if nil or none,
 * throws {@link LuaError} otherwise
 * @throws LuaError if was not numeric or nil or none.
 * @see #optdouble(double)
 * @see #optint(int)
 * @see #checkint()
 * @see #toint()
 * @see #tonumber()
 * @see #isnumber()
 * @see #TNUMBER
 */
- (LOLuaInteger *)optInteger:(LOLuaInteger *)defval;

/** Check that optional argument is a number or string convertible to number and return as long
 * @param defval long to return if {@code this} is nil or none
 * @return {@code this} cast to long if numeric,
 * {@code defval} if nil or none,
 * throws {@link LuaError} otherwise
 * @throws LuaError if was not numeric or nil or none.
 * @see #optdouble(double)
 * @see #optint(int)
 * @see #checkint()
 * @see #toint()
 * @see #tonumber()
 * @see #isnumber()
 * @see #TNUMBER
 */
- (long)optLong:(long)defval;

/** Check that optional argument is a number or string convertible to number and return as {@link LuaNumber}
 * @param defval {@link LuaNumber} to return if {@code this} is nil or none
 * @return {@code this} cast to {@link LuaNumber} if numeric,
 * {@code defval} if nil or none,
 * throws {@link LuaError} otherwise
 * @throws LuaError if was not numeric or nil or none.
 * @see #optdouble(double)
 * @see #optlong(long)
 * @see #optint(int)
 * @see #checkint()
 * @see #toint()
 * @see #tonumber()
 * @see #isnumber()
 * @see #TNUMBER
 */
- (LOLuaNumber *)optNumber:(LOLuaNumber *)defval;

/** Check that optional argument is a string or number and return as NSString
 * @param defval {@link LuaString} to return if {@code this} is nil or none
 * @return {@code this} converted to String if a string or number,
 * {@code defval} if nil or none,
 * throws {@link LuaError} if some other type
 * @throws LuaError if was not a string or number or nil or none.
 * @see #tojstring()
 * @see #optstring(LuaString)
 * @see #checkjstring()
 * @see #toString()
 * @see #TSTRING
 */
- (NSString *)optNSString:(NSString *)defval;

/** Check that optional argument is a string or number and return as {@link LuaString}
 * @param defval {@link LuaString} to return if {@code this} is nil or none
 * @return {@code this} converted to {@link LuaString} if a string or number,
 * {@code defval} if nil or none,
 * throws {@link LuaError} if some other type
 * @throws LuaError if was not a string or number or nil or none.
 * @see #tojstring()
 * @see #optjstring(String)
 * @see #checkstring()
 * @see #toString()
 * @see #TSTRING
 */
- (LOLuaString *)optString:(LOLuaString *)defval;

/** Check that optional argument is a table and return as {@link LuaTable}
 * @param defval {@link LuaTable} to return if {@code this} is nil or none
 * @return {@code this} cast to {@link LuaTable} if a table,
 * {@code defval} if nil or none,
 * throws {@link LuaError} if some other type
 * @throws LuaError if was not a table or nil or none.
 * @see #checktable()
 * @see #istable()
 * @see #TTABLE
 */
- (LOLuaTable *)optTable:(LOLuaTable *)defval;

/** Check that optional argument is a thread and return as {@link LuaThread}
 * @param defval {@link LuaThread} to return if {@code this} is nil or none
 * @return {@code this} cast to {@link LuaTable} if a thread,
 * {@code defval} if nil or none,
 * throws {@link LuaError} if some other type
 * @throws LuaError if was not a thread or nil or none.
 * @see #checkthread()
 * @see #isthread()
 * @see #TTHREAD
 */
- (LOLuaThread *)optThread:(LOLuaThread *)defval;

/** Check that optional argument is a userdata and return the Object instance
 * @param defval Object to return if {@code this} is nil or none
 * @return Object instance of the userdata if a {@link LuaUserdata},
 * {@code defval} if nil or none,
 * throws {@link LuaError} if some other type
 * @throws LuaError if was not a userdata or nil or none.
 * @see #checkuserdata()
 * @see #isuserdata()
 * @see #optuserdata(Class, Object)
 * @see #TUSERDATA
 */
- (id)optUserData:(id)defval;

/** Check that optional argument is a userdata whose instance is of a type
 * and return the Object instance
 * @param c Class to test userdata instance against
 * @param defval Object to return if {@code this} is nil or none
 * @return Object instance of the userdata if a {@link LuaUserdata} and instance is assignable to {@code c},
 * {@code defval} if nil or none,
 * throws {@link LuaError} if some other type
 * @throws LuaError if was not a userdata whose instance is assignable to {@code c} or nil or none.
 * @see #checkuserdata(Class)
 * @see #isuserdata(Class)
 * @see #optuserdata(Object)
 * @see #TUSERDATA
 */
- (id)optUserData:(Class)c defval:(id)defval;

/** Perform argument check that this is not nil or none.
 * @param defval {@link LuaValue} to return if {@code this} is nil or none
 * @return {@code this} if not nil or none, else {@code defval}
 * @see #NIL
 * @see #NONE
 * @see #isnil()
 * @see Varargs#isnoneornil(int)
 * @see #TNIL
 * @see #TNONE
 */
- (LOLuaValue *)optValue:(LOLuaValue *)defval;

/** Check that the value is a {@link LuaBoolean},
 * or throw {@link LuaError} if not
 * @return boolean value for {@code this} if it is a {@link LuaBoolean}
 * @throws LuaError if not a {@link LuaBoolean}
 * @see #optboolean(boolean)
 * @see #TBOOLEAN
 */
- (BOOL)checkBoolean;

/** Check that the value is a {@link LuaClosure} ,
 * or throw {@link LuaError} if not
 * <p>
 * {@link LuaClosure} is a subclass of {@link LuaFunction} that interprets lua bytecode.
 * @return {@code this} cast as {@link LuaClosure}
 * @throws LuaError if not a {@link LuaClosure}
 * @see #checkfunction()
 * @see #optclosure(LuaClosure)
 * @see #isclosure()
 * @see #TFUNCTION
 */
- (LOLuaClosure *)checkClosure;

/** Check that the value is numeric and return the value as a double,
 * or throw {@link LuaError} if not numeric
 * <p>
 * Values that are {@link LuaNumber} and values that are {@link LuaString}
 * that can be converted to a number will be converted to double.
 * @return value cast to a double if numeric
 * @throws LuaError if not a {@link LuaNumber} or is a {@link LuaString} that can't be converted to number
 * @see #checkint()
 * @see #checkinteger()
 * @see #checklong()
 * @see #optdouble(double)
 * @see #TNUMBER
 */
- (double)checkDouble;

/** Check that the value is a function , or throw {@link LuaError} if not
 * <p>
 * A {@link LuaFunction} may either be a Java function that implements
 * functionality directly in Java,  or a {@link LuaClosure}
 * which is a {@link LuaFunction} that executes lua bytecode.
 * @return {@code this} if it is a lua function or closure
 * @throws LuaError if not a function
 * @see #checkclosure()
 */
- (LOLuaFunction *)checkFunction;

/** Check that the value is a Globals instance, or throw {@link LuaError} if not
 * <p>
 * {@link Globals} are a special {@link LuaTable} that establish the default global environment.
 * @return {@code this} if if an instance fof {@link Globals}
 * @throws LuaError if not a {@link Globals} instance.
 */
- (LOGlobals *)checkGlobals;

/** Check that the value is numeric, and convert and cast value to int, or throw {@link LuaError} if not numeric
 * <p>
 * Values that are {@link LuaNumber} will be cast to int and may lose precision.
 * Values that are {@link LuaString} that can be converted to a number will be converted,
 * then cast to int, so may also lose precision.
 * @return value cast to a int if numeric
 * @throws LuaError if not a {@link LuaNumber} or is a {@link LuaString} that can't be converted to number
 * @see #checkinteger()
 * @see #checklong()
 * @see #checkdouble()
 * @see #optint(int)
 * @see #TNUMBER
 */
- (int)checkInt;

/** Check that the value is numeric, and convert and cast value to int, or throw {@link LuaError} if not numeric
 * <p>
 * Values that are {@link LuaNumber} will be cast to int and may lose precision.
 * Values that are {@link LuaString} that can be converted to a number will be converted,
 * then cast to int, so may also lose precision.
 * @return value cast to a int and wrapped in {@link LuaInteger} if numeric
 * @throws LuaError if not a {@link LuaNumber} or is a {@link LuaString} that can't be converted to number
 * @see #checkint()
 * @see #checklong()
 * @see #checkdouble()
 * @see #optinteger(LuaInteger)
 * @see #TNUMBER
 */
- (LOLuaInteger *)checkInteger;


/** Check that the value is numeric, and convert and cast value to long, or throw {@link LuaError} if not numeric
 * <p>
 * Values that are {@link LuaNumber} will be cast to long and may lose precision.
 * Values that are {@link LuaString} that can be converted to a number will be converted,
 * then cast to long, so may also lose precision.
 * @return value cast to a long if numeric
 * @throws LuaError if not a {@link LuaNumber} or is a {@link LuaString} that can't be converted to number
 * @see #checkint()
 * @see #checkinteger()
 * @see #checkdouble()
 * @see #optlong(long)
 * @see #TNUMBER
 */
- (long)checkLong;

/** Check that the value is numeric, and return as a LuaNumber if so, or throw {@link LuaError}
 * <p>
 * Values that are {@link LuaString} that can be converted to a number will be converted and returned.
 * @return value as a {@link LuaNumber} if numeric
 * @throws LuaError if not a {@link LuaNumber} or is a {@link LuaString} that can't be converted to number
 * @see #checkint()
 * @see #checkinteger()
 * @see #checkdouble()
 * @see #checklong()
 * @see #optnumber(LuaNumber)
 * @see #TNUMBER
 */
- (LOLuaNumber *)checkNumber;

/** Check that the value is numeric, and return as a LuaNumber if so, or throw {@link LuaError}
 * <p>
 * Values that are {@link LuaString} that can be converted to a number will be converted and returned.
 * @param msg String message to supply if conversion fails
 * @return value as a {@link LuaNumber} if numeric
 * @throws LuaError if not a {@link LuaNumber} or is a {@link LuaString} that can't be converted to number
 * @see #checkint()
 * @see #checkinteger()
 * @see #checkdouble()
 * @see #checklong()
 * @see #optnumber(LuaNumber)
 * @see #TNUMBER
 */
- (LOLuaNumber *)checkNumber:(NSString *)msg;

/** Convert this value to a NSString.
 * <p>
 * The string representations here will roughly match what is produced by the
 * C lua distribution, however hash codes have no relationship,
 * and there may be differences in number formatting.
 * @return String representation of the value
 * @see #checkstring()
 * @see #optjstring(String)
 * @see #tojstring()
 * @see #isstring
 * @see #TSTRING
 */
- (NSString *)checkNSString;

/** Check that this is a lua string, or throw {@link LuaError} if it is not.
 * <p>
 * In lua all numbers are strings, so this will succeed for
 * anything that derives from {@link LuaString} or {@link LuaNumber}.
 * Numbers will be converted to {@link LuaString}.
 *
 * @return {@link LuaString} representation of the value if it is a {@link LuaString} or {@link LuaNumber}
 * @throws LuaError if {@code this} is not a {@link LuaTable}
 * @see #checkjstring()
 * @see #optstring(LuaString)
 * @see #tostring()
 * @see #isstring()
 * @see #TSTRING
 */
- (LOLuaString *)checkString;

/** Check that this is a {@link LuaTable}, or throw {@link LuaError} if it is not
 * @return {@code this} if it is a {@link LuaTable}
 * @throws LuaError if {@code this} is not a {@link LuaTable}
 * @see #istable()
 * @see #opttable(LuaTable)
 * @see #TTABLE
 */
- (LOLuaTable *)checkTable;

/** Check that this is a {@link LuaThread}, or throw {@link LuaError} if it is not
 * @return {@code this} if it is a {@link LuaThread}
 * @throws LuaError if {@code this} is not a {@link LuaThread}
 * @see #isthread()
 * @see #optthread(LuaThread)
 * @see #TTHREAD
 */
- (LOLuaThread *)checkThread;

/** Check that this is a {@link LuaUserdata}, or throw {@link LuaError} if it is not
 * @return {@code this} if it is a {@link LuaUserdata}
 * @throws LuaError if {@code this} is not a {@link LuaUserdata}
 * @see #isuserdata()
 * @see #optuserdata(Object)
 * @see #checkuserdata(Class)
 * @see #TUSERDATA
 */
- (id)checkUserData;

/** Check that this is a {@link LuaUserdata}, or throw {@link LuaError} if it is not
 * @return {@code this} if it is a {@link LuaUserdata}
 * @throws LuaError if {@code this} is not a {@link LuaUserdata}
 * @see #isuserdata(Class)
 * @see #optuserdata(Class, Object)
 * @see #checkuserdata()
 * @see #TUSERDATA
 */
- (id)checkUserData:(Class)c;

/** Check that this is not the value {@link #NIL}, or throw {@link LuaError} if it is
 * @return {@code this} if it is not {@link #NIL}
 * @throws LuaError if {@code this} is {@link #NIL}
 * @see #optvalue(LuaValue)
 */
- (LOLuaValue *)checkNotNil;

/** Return true if this is a valid key in a table index operation.
 * @return true if valid as a table key, otherwise false
 * @see #isnil()
 * @see #isinttype()
 */
- (BOOL)isValidKey;

/**
 * Throw a {@link LuaError} with a particular message
 * @param message String providing message details
 * @throws LuaError in all cases
 */
+ (LOLuaValue *)error:(NSString *)message;














































/**
 * Throw a {@link LuaError} indicating an invalid argument was supplied to a function
 * @param expected String naming the type that was expected
 * @throws LuaError in all cases
 */
- (LOLuaValue *)argError:(NSString *)expected;

/**
 * Throw a {@link LuaError} indicating an invalid argument was supplied to a function
 * @param iarg index of the argument that was invalid, first index is 1
 * @param msg String providing information about the invalid argument
 * @throws LuaError in all cases
 */
+ (LOLuaValue *)argError:(int)iarg msg:(NSString *)msg;

@end
