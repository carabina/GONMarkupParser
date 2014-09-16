//
//  GONMarkupParserManager.h
//  GONMarkupParserSample
//
//  Created by Nicolas Goutaland on 25/07/14.
//  Copyright (c) 2014 Nicolas Goutaland. All rights reserved.
//
//  This class help you to manage shared parsers
//  It also provide a default shared parser for your application

#import "GONMarkupParser.h"

@interface GONMarkupParserManager : NSObject
// Shared parsers management
/* Return shared parser instance.
 * Shared parser is preconfigured to handle all default tags
 */
+ (GONMarkupParser *)sharedParser;

/* Retrieve a parser registered under given key
 * Return nil if not found
 */
+ (GONMarkupParser *)registeredMarkupParserForKey:(NSString *)aKey;

/* Register given parser under key
 * Use this method to be able to share a parser
 */
+ (void)registerMarkupParser:(GONMarkupParser *)aParser forKey:(NSString *)aKey;

/* Unregister parser under given key */
+ (void)unregisterMarkupParserForKey:(NSString *)aKey;

@end