#import "Three20/TTGlobal.h"

@class TTURLRequest;

@interface TTURLCache : NSObject {
  NSString* _cachePath;
  NSMutableDictionary* _imageCache;
  NSMutableArray* _imageSortedList;
  NSUInteger _totalPixelCount;
  NSUInteger _maxPixelCount;
  NSInteger _totalLoading;
  NSTimeInterval _invalidationAge;
  BOOL _disableDiskCache;
  BOOL _disableImageCache;
}

/**
 * Disables the disk cache.
 */
@property(nonatomic) BOOL disableDiskCache;

/**
 * Disables the in-memory cache for images.
 */
@property(nonatomic) BOOL disableImageCache;

/**
 * Gets the path to the directory of the disk cache.
 */
@property(nonatomic,copy) NSString* cachePath;

/**
 * The maximum number of pixels to keep in memory for cached images.
 *
 * Setting this to zero will allow an unlimited number of images to be cached.  The default
 * is enough to hold roughly 25 small images.
 */
@property(nonatomic) NSUInteger maxPixelCount;

/**
 * The amount of time to set back the modification timestamp on files when invalidating them.
 */
@property(nonatomic) NSTimeInterval invalidationAge;

/**
 * Gets the shared cache singleton used across the application.
 */
+ (TTURLCache*)sharedCache;

/**
 * Sets the shared cache singleton used across the application.
 */
+ (void)setSharedCache:(TTURLCache*)cache;

/**
 * Gets the path to the default directory of the disk cache.
 */
+ (NSString*)defaultCachePath;

/**
 * Gets the key that would be used to cache a URL response.
 */
- (NSString *)keyForURL:(NSString*)url;

/**
 * Determines if there is a cache entry for a URL.
 */
- (BOOL)hasDataForURL:(NSString*)url;

/**
 * Gets the path in the cache where a URL may be stored.
 */
- (NSString*)cachePathForURL:(NSString*)url;

/**
 * Gets the path in the cache where a key may be stored.
 */
- (NSString*)cachePathForKey:(NSString*)key;

/**
 * Gets the data for a URL from the cache if it exists.
 *
 * @return nil if the URL is not cached. 
 */
- (NSData*)dataForURL:(NSString*)url;

/**
 * Gets the data for a URL from the cache if it exists and is newer than a minimum timestamp.
 *
 * @return nil if hthe URL is not cached or if the cache entry is older than the minimum.
 */
- (NSData*)dataForURL:(NSString*)url expires:(NSTimeInterval)expirationAge
  timestamp:(NSDate**)timestamp;
- (NSData*)dataForKey:(NSString*)key expires:(NSTimeInterval)expirationAge
  timestamp:(NSDate**)timestamp;

/**
 * Gets an image from the in-memory image cache.
 *
 * @return nil if the URL is not cached.
 */
- (id)imageForURL:(NSString*)url;

/**
 * Stores a data on disk.
 */
- (void)storeData:(NSData*)data forURL:(NSString*)url;
- (void)storeData:(NSData*)data forKey:(NSString*)key;

/**
 * Stores an image the memory cache.
 */
- (void)storeImage:(UIImage*)image forURL:(NSString*)url;
- (void)storeImage:(UIImage*)image forKey:(NSString*)key;

/**
 * Convenient way to create a temporary URL for some data and cache it in memory.
 *
 * @return The temporary URL
 */
- (NSString*)storeTemporaryImage:(UIImage*)image toDisk:(BOOL)toDisk;

/**
 * Convenient way to create a temporary URL for some data and cache in on disk.
 *
 * @return The temporary URL
 */
- (NSString*)storeTemporaryData:(NSData*)data;

/**
 * Moves the data currently stored under one URL to another URL.
 * 
 * This is handy when you are caching data at a temporary URL while the permanent URL is being
 * retrieved from a server.  Once you know the permanent URL you can use this to move the data.
 */ 
- (void)moveDataForURL:(NSString*)oldURL toURL:(NSString*)newURL;

/**
 * Removes the data for a URL from the memory cache and optionally from the disk cache.
 */
- (void)removeURL:(NSString*)url fromDisk:(BOOL)fromDisk;

/**
 * 
 */
- (void)removeKey:(NSString*)key;

/** 
 * Erases the memory cache and optionally the disk cache.
 */
- (void)removeAll:(BOOL)fromDisk;

/** 
 * Invalidates the file in the disk cache so that its modified timestamp is the current
 * time minus the default cache expiration age.
 *
 * This ensures that the next time the URL is requested from the cache it will be loaded
 * from the network if the default cache expiration age is used.
 */
- (void)invalidateURL:(NSString*)url;

/**
 *
 */
- (void)invalidateKey:(NSString*)key;

/**
 * Invalidates all files in the disk cache according to rules explained in `invalidateURL`.
 */
- (void)invalidateAll;

- (void)logMemoryUsage;

@end