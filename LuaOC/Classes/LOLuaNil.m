//
//  LOLuaNil.m
//  LuaOC
//
//  Created by 刘旭 on 2018/12/20.
//

#import "LOLuaNil.h"

@implementation LOLuaNil

static LOLuaNil *_defaultNil = nil;
+ (instancetype)defaultNil
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _defaultNil = [[LOLuaNil alloc] init];
    });
    return _defaultNil;
}

@end
