//
//  Varargs.m
//  Expecta
//
//  Created by 刘旭 on 2018/12/19.
//

#import "LOVarargs.h"
#import "LOLuaValue.h"
#import "LOLuaNumber.h"

@implementation LOVarargs

- (LOVarargs *)eval
{
    return self;
}

- (BOOL)isTailcall
{
    return NO;
}

- (int)type:(int)i
{
    return [[self arg:i] type];
}

- (BOOL)isFunction:(int)i
{
    return [self arg:i].isFunction;
}

- (BOOL)isNumber:(int)i
{
    return [self arg:i].isNumber;
}

- (BOOL)isString:(int)i
{
    return [self arg:i].isString;
}

- (BOOL)isTable:(int)i
{
    return [self arg:i].isTable;
}

- (BOOL)isThread:(int)i
{
    return [self arg:i].isThread;
}

- (BOOL)isUserData:(int)i
{
    return [self arg:i].isUserData;
}

- (BOOL)isValue:(int)i
{
    return i>0 && i<=self.narg;
}

- (BOOL)optBoolean:(int)i defval:(BOOL)defval
{
    return [[self arg:i] optBoolean:defval];
}

- (LOLuaClosure *)optClosure:(int)i defval:(LOLuaClosure *)defval
{
    return [[self arg:i] optClosure:defval];
}

- (LOLuaFunction *)optFunction:(int)i defval:(LOLuaFunction *)defval
{
    return [[self arg:i] optFunction:defval];
}

- (int)optInt:(int)i defval:(int)defval
{
    return [[self arg:i] optInt:defval];
}

- (LOLuaInteger *)optInteger:(int)i defval:(LOLuaInteger *)defval
{
    return [[self arg:i] optInteger:defval];
}

- (long)optLong:(int)i defval:(long)defval
{
    return [[self arg:i] optLong:defval];
}

- (LOLuaNumber *)optNumber:(int)i defval:(LOLuaNumber *)defval
{
    return [[self arg:i] optNumber:defval];
}

- (NSString *)optNSString:(int)i defval:(NSString *)defval
{
    return [[self arg:i] optNSString:defval];
}

- (LOLuaString *)optString:(int)i defval:(LOLuaString *)defval
{
    return [[self arg:i] optString:defval];
}

- (LOLuaTable *)optTable:(int)i defval:(LOLuaTable *)defval
{
    return [[self arg:i] optTable:defval];
}

- (LOLuaThread *)optThread:(int)i defval:(LOLuaThread *)defval
{
    return [[self arg:i] optThread:defval];
}

- (id)optUserData:(int)i defval:(id)defval
{
    return [[self arg:i] optUserData:defval];
}

- (id)optUserData:(int)i clazz:(Class)c defval:(id)defval
{
    return [[self arg:i] optUserData:c defval:defval];
}

- (LOLuaValue *)optValue:(int)i defval:(LOLuaValue *)defval
{
    return i>0 && i<=self.narg? [self arg:i] : defval;
}

- (BOOL)checkBoolean:(int)i
{
    return [self arg:i].checkBoolean;
}

- (LOLuaClosure *)checkClosure:(int)i
{
    return [self arg:i].checkClosure;
}

- (double)checkDouble:(int)i
{
    return [self arg:i].checkDouble;
}

- (LOLuaFunction *)checkFunction:(int)i
{
    return [self arg:i].checkFunction;
}

- (int)checkInt:(int)i
{
    return [self arg:i].checkNumber.toInt;
}

- (LOLuaInteger *)checkInteger:(int)i
{
    return [self arg:i].checkInteger;
}

- (long)checkLong:(int)i
{
    return [self arg:i].checkNumber.toLong;
}

- (LOLuaNumber *)checkNumber:(int)i
{
    return [self arg:i].checkNumber;
}

- (NSString *)checkNSString:(int)i
{
    return [self arg:i].checkNSString;
}

- (LOLuaString *)checkString:(int)i
{
    return [self arg:i].checkString;
}

- (LOLuaTable *)checkTable:(int)i
{
    return [self arg:i].checkTable;
}

- (LOLuaThread *)checkThread:(int)i
{
    return [self arg:i].checkThread;
}

- (id)checkUserData:(int)i
{
    return [self arg:i].checkUserData;
}

- (id)checkUserData:(int)i clazz:(Class)c
{
    return [[self arg:i] checkUserData:c];
}

- (id)checkValue:(int)i
{
    return i<=self.narg? [self arg:i]: [LOLuaValue argError:i msg:@"value expected"];
}

- (LOLuaValue *)checkNotNil:(int)i
{
    return [self arg:i].checkNotNil;
}

- (void)argCheck:(BOOL)test index:(int)i message:(NSString *)msg
{
    if (!test) [LOLuaValue argError:i msg:@"value expected"];
}

- (BOOL)isNoneOrNil:(int)i
{
    return i>self.narg || [self arg:i].isNil;
}

- (BOOL)toBoolean:(int)i
{
    return [self arg:i].toBoolean;
}

- (Byte)toByte:(int)i
{
    return [self arg:i].toByte;
}

- (char)toChar:(int)i
{
    return [self arg:i].toChar;
}

- (double)toDouble:(int)i
{
    return [self arg:i].toDouble;
}

- (float)toFloat:(int)i
{
    return [self arg:i].toFloat;
}

- (int)toInt:(int)i
{
    return [self arg:i].toInt;
}

- (long)toLong:(int)i
{
    return [self arg:i].toLong;
}

- (NSString *)toNSString:(int)i
{
    return [self arg:i].toNSString;
}

- (short)toShort:(int)i
{
    return [self arg:i].toShort;
}

-(id)toUserData:(int)i
{
    return [self arg:i].toUserData;
}

- (id)toUserData:(int)i clazz:(Class)c
{
    return [[self arg:i] toUserData:c];
}

- (NSString *)toNSString
{
    NSMutableString *ms = [NSMutableString stringWithString:@"("];
    for (int i = 1, n = self.narg; i <= n; i++) {
        if (i>1) {
            [ms appendString:@","];
        }
        [ms appendString:[self arg:i].toString];
    }
    return ms.copy;
}

- (NSString *)toString
{
    return self.toNSString;
}
















@end
