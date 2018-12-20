//
//  LOLuaValue.m
//  Expecta
//
//  Created by 刘旭 on 2018/12/19.
//

#import "LOLuaValue.h"
#import "LOLuaError.h"
#import "LOLuaNil.h"

@implementation LOLuaValue

+ (LOLuaValue *)NIL
{
    return [LOLuaNil defaultNil];
}

+ (LOLuaValue *)NONE
{
    return [LOLuaNil defaultNil];
}

- (BOOL)isBoolean
{
    return NO;
}

- (BOOL)isClosure
{
    return NO;
}

- (BOOL)isFunction
{
    return NO;
}

- (BOOL)isInt
{
    return NO;
}

- (BOOL)isIntType
{
    return NO;
}

- (BOOL)isLong
{
    return NO;
}

- (BOOL)isNil
{
    return NO;
}

- (BOOL)isNumber
{
    return NO;
}

- (BOOL)isString
{
    return NO;
}

- (BOOL)isThread
{
    return NO;
}

- (BOOL)isTable
{
    return NO;
}

- (BOOL)isUserData
{
    return NO;
}

- (BOOL)isUserData:(Class)c
{
    return NO;
}

- (BOOL)toBoolean
{
    return YES;
}

- (Byte)toByte
{
    return 0;
}

- (char)toChar
{
    return 0;
}

- (double)toDouble
{
    return 0;
}

- (float)toFloat
{
    return 0.f;
}

- (int)toInt
{
    return 0;
}

- (long)toLong
{
    return 0;
}

- (short)toShort
{
    return 0;
}

- (NSString *)toNSString
{
    return [NSString stringWithFormat:@"%@:%lu", self.typeName, self.hash];
}

- (id)toUserData
{
    return nil;
}

- (id)toUserData:(Class)c
{
    return nil;
}

- (NSString *)toString
{
    return self.toNSString;
}

- (LOLuaNumber *)toNumber
{
    return nil;
}

- (LOLuaValue *)toValueString
{
    return nil;
}

- (BOOL)optBoolean:(BOOL)defval
{
    [self argError:@"boolean"];
    return NO;
}

- (LOLuaClosure *)optClosure:(LOLuaClosure *)defval
{
    [self argError:@"closure"];
    return nil;
}

- (double)optDouble:(double)defval
{
    [self argError:@"double"];
    return 0;
}

- (LOLuaFunction *)optFunction:(LOLuaFunction *)defval
{
    [self argError:@"function"];
    return nil;
}

- (int)optInt:(int)defval
{
    [self argError:@"int"];
    return 0;
}

- (LOLuaInteger *)optInteger:(LOLuaInteger *)defval
{
    [self argError:@"integer"];
    return nil;
}

- (long)optLong:(long)defval
{
    [self argError:@"long"];
    return 0;
}

- (LOLuaNumber *)optNumber:(LOLuaNumber *)defval
{
    [self argError:@"number"];
    return nil;
}

- (NSString *)optNSString:(NSString *)defval
{
    [self argError:@"NSString"];
    return nil;
}

- (LOLuaString *)optString:(LOLuaString *)defval
{
    [self argError:@"string"];
    return nil;
}

- (LOLuaTable *)optTable:(LOLuaTable *)defval
{
    [self argError:@"table"];
    return nil;
}

- (LOLuaThread *)optThread:(LOLuaThread *)defval
{
    [self argError:@"thread"];
    return nil;
}

- (id)optUserData:(id)defval
{
    [self argError:@"object"];
    return nil;
}

- (id)optUserData:(Class)c defval:(id)defval
{
    [self argError:NSStringFromClass(c)];
    return nil;
}

- (LOLuaValue *)optValue:(LOLuaValue *)defval
{
    return self;
}

- (BOOL)checkBoolean
{
    [self argError:@"boolean"];
    return NO;
}

- (LOLuaClosure *)checkClosure
{
    [self argError:@"closure"];
    return nil;
}

- (double)checkDouble
{
    [self argError:@"double"];
    return 0;
}

- (LOLuaFunction *)checkFunction
{
    [self argError:@"function"];
    return nil;
}

- (LOGlobals *)checkGlobals
{
    [self argError:@"globals"];
    return nil;
}

- (int)checkInt
{
    [self argError:@"int"];
    return 0;
}

- (LOLuaInteger *)checkInteger
{
    [self argError:@"integer"];
    return nil;
}

- (long)checkLong
{
    [self argError:@"long"];
    return 0;
}

- (LOLuaNumber *)checkNumber
{
    [self argError:@"number"];
    return nil;
}

- (LOLuaNumber *)checkNumber:(NSString *)msg
{
    [self argError:@"msg"];
    return nil;
}

- (NSString *)checkNSString
{
    [self argError:@"NSString"];
    return nil;
}

- (LOLuaString *)checkString
{
    [self argError:@"string"];
    return nil;
}

- (LOLuaTable *)checkTable
{
    [self argError:@"table"];
    return nil;
}

- (LOLuaThread *)checkThread
{
    [self argError:@"thread"];
    return nil;
}

- (id)checkUserData
{
    [self argError:@"userdata"];
    return nil;
}

- (id)checkUserData:(Class)c
{
    [self argError:@"userdata"];
    return nil;
}

- (LOLuaValue *)checkNotNil
{
    return self;
}

- (BOOL)isValidKey
{
    return YES;
}

+ (LOLuaValue *)error:(NSString *)message
{
    @throw [LOLuaError exceptionWithName:@"LuaError" reason:message userInfo:nil];
}































- (LOLuaValue *)argError:(NSString *)expected
{
    @throw [LOLuaError exceptionWithName:@"LuaArgError"
                                  reason:[NSString stringWithFormat:@"bad argument: %@ expected, got %@",expected, self.typeName]
                                userInfo:nil];
}

+ (LOLuaValue *)argError:(int)iarg msg:(NSString *)msg
{
    @throw [LOLuaError exceptionWithName:@"LuaArgError"
                                  reason:[NSString stringWithFormat:@"bad argument #%d : %@",iarg, msg]
                                userInfo:nil];
}

@end
