//
//  BXResourceElement.m
//  Karakuri Box
//
//  Created by numata on 10/02/27.
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import "BXResourceElement.h"
#import "NSString+UUID.h"


@interface BXResourceElement ()

- (void)setParent:(BXResourceElement*)anElem;

@end


@implementation BXResourceElement

#pragma mark -
#pragma mark 初期化・クリーンアップ

- (id)initWithName:(NSString*)name
{
    self = [super init];
    if (self) {
        mResourceName = [name copy];
        mChildElements = [NSMutableArray new];
        
        mResourceUUID = [[NSString generateUUIDString] retain];
        
        mGroupID = 0;
        mResourceID = 99;
    }
    return self;
}

- (void)dealloc
{
    [mResourceUUID release];
    [mResourceName release];
    [mChildElements release];

    [super dealloc];
}

- (BXDocument*)document
{
    BXDocument* ret = mDocument;
    if (!ret && mParentElement) {
        ret = [mParentElement document];
    }
    return ret;
}

- (void)setDocument:(BXDocument*)aDocument
{
    mDocument = aDocument;
}


#pragma mark -
#pragma mark 項目の管理

- (NSString*)localizedName
{
    if ([mResourceName hasPrefix:@"*"]) {
        return NSLocalizedString(mResourceName, nil);
    }
    return [NSString stringWithFormat:@"%d: %@", mResourceID, mResourceName];
}

- (BOOL)isExpandable
{
    return NO;
}

- (BOOL)isGroupItem
{
    return NO;
}

- (NSString*)resourceUUID
{
    return mResourceUUID;
}

- (int)groupID
{
    return mGroupID;
}

- (int)resourceID
{
    return mResourceID;
}

- (NSString*)resourceName
{
    return mResourceName;
}

- (void)setGroupID:(int)theID
{
    mGroupID = theID;
}

- (void)setResourceID:(int)theID
{
    mResourceID = theID;
    
    if (mParentElement) {
        [mParentElement sortChildrenByResourceID];
    }
}

- (void)setResourceName:(NSString*)name
{
    [mResourceName release];
    mResourceName = [name copy];
}


#pragma mark -
#pragma mark 子供の管理

- (void)addChild:(BXResourceElement*)anElem
{
    [anElem setParent:self];
    [mChildElements addObject:anElem];
}

- (int)childCount
{
    return [mChildElements count];
}

- (BXResourceElement*)childAtIndex:(int)index
{
    return [mChildElements objectAtIndex:index];
}

- (BXResourceElement*)childWithResourceID:(int)resourceID
{
    int childCount = [mChildElements count];
    for (int i = 0; i < childCount; i++) {
        BXResourceElement* aChild = [mChildElements objectAtIndex:i];
        if ([aChild resourceID] == resourceID) {
            return aChild;
        }
    }
    
    return nil;
}

- (BXResourceElement*)childWithResourceUUID:(NSString*)theUUID
{
    int childCount = [mChildElements count];
    for (int i = 0; i < childCount; i++) {
        BXResourceElement* aChild = [mChildElements objectAtIndex:i];
        if ([[aChild resourceUUID] isEqualToString:theUUID]) {
            return aChild;
        }
    }
    
    return nil;
}

- (void)removeChild:(BXResourceElement*)anElem
{
    [anElem setParent:nil];
    [mChildElements removeObject:anElem];
}

- (void)setParent:(BXResourceElement*)anElem
{
    mParentElement = anElem;
}

- (void)sortChildrenByResourceID
{
    NSSortDescriptor* sortDesc = [[[NSSortDescriptor alloc] initWithKey:@"resourceID"
                                                              ascending:YES] autorelease];

    [mChildElements sortUsingDescriptors:[NSArray arrayWithObject:sortDesc]];
}

- (NSString*)description
{
    return [self localizedName];
}

- (NSDictionary*)elementInfo
{
    return [NSDictionary dictionary];
}

- (void)restoreElementInfo:(NSDictionary*)theInfo document:(BXDocument*)document
{
    // Do nothing
}

@end


@implementation BXResourceElement (Export)

- (void)exportToFileHandle:(NSFileHandle*)fileHandle
{
    // Do nothing.
}

@end


