//
//  GONMarkup.h
//  GONMarkupParserSample
//
//  Created by Nicolas Goutaland on 25/06/14.
//  Copyright (c) 2014 Nicolas Goutaland All rights reserved.
//
// Simple class defining a markup
// You can use it as it, or override it to add more configuration
//
// Tag name will be stored lowercased, so be careful when using multiple tags
//
// Tag lifecycle :
// - canHandleTag: may be called to determine if markup match found tag
// - Once a tag is found, openingMarkupFound:configuration:context: method will be called
// - Before parser append extracted string to result, updatedContentString:context: will be called, allowing tag to update it
// - Once tag is closed, closingMarkupFound:configuration:context: method will be called
//
// Markup instance will be reused each time a matching tag is found. To persist data, use context parameter.
@class GONMarkupParser;

@interface GONMarkup : NSObject
/* Class constructor */
+ (instancetype)markupForTag:(NSString *)tag;

/* Default constructor */
- (id)initWithTag:(NSString *)tag;

/* This method will be called if markup is matching current opening tag.
 * Object is responsible to update attributed string parameters in "configurationDictionary"
 *
 * "tag" is matching tag, allowing you to extract parameters
 * "context" is a mutable dictionary used by marker to add contextual information. This dictionary is shared throught all markers in a parser and is reset each time a new parse is started
 * It is used for example by list markers to handle list type, tabulation index and count
 *
 * You should override this method to implement new behavior
 */
- (void)openingMarkupFound:(NSString *)tag configuration:(NSMutableDictionary *)configurationDictionary context:(NSMutableDictionary *)context;

/* Allows marker to prefix its content string
 * This method is called right after opening markup
 */
- (NSString *)prefixStringForContext:(NSMutableDictionary *)context;

/* This method will be called once current marker tag is closed
 * This allows marker to update string content
 * "context" is the same as in openingMarkupFound:configuration:fromTag:context:
 *
 * Default implementation return input string
 */
- (NSString *)updatedContentString:(NSString *)string context:(NSMutableDictionary *)context;

/* Allows marker to suffix its content string
 * This method is called right after opening markup
 */
- (NSString *)suffixStringForContext:(NSMutableDictionary *)context;

/* This method will be called if markup is matching current closing tag.
 * Object is responsible to update attributed string parameters in "configurationDictionary"
 *
 * "tag" is matching tag, allowing you to extract parameters
 * "context" is a mutable dictionary use by marker to add contextual information. This dictionary is shared throught all markers in a parser and is reset each time a new parse is started
 * It is used for example by list markers to handle list type, tabulation index and count
 *
 * You should override this method to implement new behavior
 */
- (void)closingMarkupFound:(NSString *)tag configuration:(NSMutableDictionary *)configurationDictionary context:(NSMutableDictionary *)context;

/* Ask markup rule if it can handle given tag.
 * This method is not always called, because tag property is used first to check tag handling
 * Default implementation compare given tag to Markup tag.
 *
 * If both strings are equals (caseInsensitiveCompare: == NSOrderedSame), method will return YES
 * If Markup tag start with tested tag, and is followed by a space, method will return YES
 * All other cases will return NO
 *
 * Examples :
 *
 * Tested tag        |  Markup tag         |    result
 * ----------------------------------------------------
 * red               |  red                |    YES
 * redColor          |  red                |    NO
 * red               |  redColor           |    NO
 * color             |  color              |    YES
 * color             |  colorRed           |    NO
 * colorRed          |  color              |    NO
 * color red         |  color              |    YES
 * color value="red" |  color              |    YES
 *
 * You can override this method to implement your own comparison method
 * "tag" will be lowercased, and trimmed
 */
- (BOOL)canHandleTag:(NSString *)tag;

@property (nonatomic, copy, readonly) NSString *tag;            // Have to be unique. Used to speed up rules matching, when using tags without parameters
@property (nonatomic, weak, readonly) GONMarkupParser *parser;  // Parser the markup is attached to
@end
