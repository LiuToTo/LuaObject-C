//
//  LOLuaError.h
//  LuaOC
//
//  Created by 刘旭 on 2018/12/20.
//

#import <Foundation/Foundation.h>

@interface LOLuaError : NSException

@property (nonatomic, assign) int level;
@property (nonatomic, copy) NSString *fileLine;
@property (nonatomic, copy) NSString *traceback;

@end
