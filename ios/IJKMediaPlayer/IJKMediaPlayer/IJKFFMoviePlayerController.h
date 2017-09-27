/*
 * IJKFFMoviePlayerController.h
 *
 * Copyright (c) 2013 Bilibili
 * Copyright (c) 2013 Zhang Rui <bbcallen@gmail.com>
 *
 * This file is part of ijkPlayer.
 *
 * ijkPlayer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ijkPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ijkPlayer; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#import "IJKMediaPlayback.h"
#import "IJKFFMonitor.h"
#import "IJKFFOptions.h"

// media meta
#define k_IJKM_KEY_FORMAT         @"format"
#define k_IJKM_KEY_DURATION_US    @"duration_us"
#define k_IJKM_KEY_START_US       @"start_us"
#define k_IJKM_KEY_BITRATE        @"bitrate"

// stream meta
#define k_IJKM_KEY_TYPE           @"type"
#define k_IJKM_VAL_TYPE__VIDEO    @"video"
#define k_IJKM_VAL_TYPE__AUDIO    @"audio"
#define k_IJKM_VAL_TYPE__UNKNOWN  @"unknown"

#define k_IJKM_KEY_CODEC_NAME      @"codec_name"
#define k_IJKM_KEY_CODEC_PROFILE   @"codec_profile"
#define k_IJKM_KEY_CODEC_LONG_NAME @"codec_long_name"

// stream: video
#define k_IJKM_KEY_WIDTH          @"width"
#define k_IJKM_KEY_HEIGHT         @"height"
#define k_IJKM_KEY_FPS_NUM        @"fps_num"
#define k_IJKM_KEY_FPS_DEN        @"fps_den"
#define k_IJKM_KEY_TBR_NUM        @"tbr_num"
#define k_IJKM_KEY_TBR_DEN        @"tbr_den"
#define k_IJKM_KEY_SAR_NUM        @"sar_num"
#define k_IJKM_KEY_SAR_DEN        @"sar_den"
// stream: audio
#define k_IJKM_KEY_SAMPLE_RATE    @"sample_rate"
#define k_IJKM_KEY_CHANNEL_LAYOUT @"channel_layout"

#define kk_IJKM_KEY_STREAMS       @"streams"

/**
 日志等级
 
 - k_IJK_LOG_UNKNOWN: 未知
 - k_IJK_LOG_DEFAULT: 默认
 - k_IJK_LOG_VERBOSE: 详细
 - k_IJK_LOG_DEBUG: 调试
 - k_IJK_LOG_INFO: 信息
 - k_IJK_LOG_WARN: 警告
 - k_IJK_LOG_ERROR: 错误
 - k_IJK_LOG_FATAL: 致命
 - k_IJK_LOG_SILENT: 无日志
 */
typedef enum IJKLogLevel {
	/// 未知
    k_IJK_LOG_UNKNOWN = 0,
	/// 默认
    k_IJK_LOG_DEFAULT = 1,

	/// 详细
    k_IJK_LOG_VERBOSE = 2,
	/// 调试
    k_IJK_LOG_DEBUG   = 3,
	/// 信息
    k_IJK_LOG_INFO    = 4,
	/// 警告
    k_IJK_LOG_WARN    = 5,
	/// 错误
    k_IJK_LOG_ERROR   = 6,
	/// 致命
    k_IJK_LOG_FATAL   = 7,
	/// 无日志
    k_IJK_LOG_SILENT  = 8,
} IJKLogLevel;


/**
 ijkPlayer ffmpeg 控制器
 */
@interface IJKFFMoviePlayerController : NSObject <IJKMediaPlayback>


/**
 初始化播放器

 @param aUrl 播放资源URL
 @param options ijk 选项
 @return IJKFFMoviePlayerController 对象
 */
- (id)initWithContentURL:(NSURL *)aUrl
             withOptions:(IJKFFOptions *)options;


/**
 初始化播放器

 @param aUrlString 播放资源 URL 字符串
 @param options ijk 选项
 @return IJKFFMoviePlayerController 对象
 */
- (id)initWithContentURLString:(NSString *)aUrlString
                   withOptions:(IJKFFOptions *)options;

/**
 就绪
 */
- (void)prepareToPlay;
/**
 播放
 */
- (void)play;
/**
 暂停
 */
- (void)pause;
/**
 停止
 */
- (void)stop;
/**
 是否正在播放

 @return 是否正在播放
 */
- (BOOL)isPlaying;
/**
 流量统计

 @return 流量
 */
- (int64_t)trafficStatistic;
/**
 丢帧率

 @return 丢帧率
 */
- (float)dropFrameRate;

/**
 是否禁止后台播放

 @param pause 后台暂停
 */
- (void)setPauseInBackground:(BOOL)pause;
/**
 是否硬解码

 @return 是否硬解码
 */
- (BOOL)isVideoToolboxOpen;

/**
 是否输出日志

 @param preferLogReport 是否输出日志
 */
+ (void)setLogReport:(BOOL)preferLogReport;
/**
 设置日志等级

 @param logLevel 日志等级
 */
+ (void)setLogLevel:(IJKLogLevel)logLevel;
/**
 检查FFmpeg版本是否匹配

 @param showAlert 是否弹窗提示
 @return FFmpeg版本是否匹配
 */
+ (BOOL)checkIfFFmpegVersionMatch:(BOOL)showAlert;
/**
 检查播放器版本是否与指定版本匹配

 @param showAlert 是否弹窗提示
 @param version 指定版本
 @return 播放器版本是否与指定版本匹配
 */
+ (BOOL)checkIfPlayerVersionMatch:(BOOL)showAlert
                            version:(NSString *)version;

/// 元数据帧率
@property(nonatomic, readonly) CGFloat fpsInMeta;
/// 输出帧率
@property(nonatomic, readonly) CGFloat fpsAtOutput;
/// 是否显示浮窗
@property(nonatomic) BOOL shouldShowHudView;

- (void)setOptionValue:(NSString *)value
                forKey:(NSString *)key
            ofCategory:(IJKFFOptionCategory)category;

- (void)setOptionIntValue:(int64_t)value
                   forKey:(NSString *)key
               ofCategory:(IJKFFOptionCategory)category;



- (void)setFormatOptionValue:       (NSString *)value forKey:(NSString *)key;
- (void)setCodecOptionValue:        (NSString *)value forKey:(NSString *)key;
- (void)setSwsOptionValue:          (NSString *)value forKey:(NSString *)key;
- (void)setPlayerOptionValue:       (NSString *)value forKey:(NSString *)key;

- (void)setFormatOptionIntValue:    (int64_t)value forKey:(NSString *)key;
- (void)setCodecOptionIntValue:     (int64_t)value forKey:(NSString *)key;
- (void)setSwsOptionIntValue:       (int64_t)value forKey:(NSString *)key;
- (void)setPlayerOptionIntValue:    (int64_t)value forKey:(NSString *)key;

@property (nonatomic, retain) id<IJKMediaUrlOpenDelegate> segmentOpenDelegate;
@property (nonatomic, retain) id<IJKMediaUrlOpenDelegate> tcpOpenDelegate;
@property (nonatomic, retain) id<IJKMediaUrlOpenDelegate> httpOpenDelegate;
@property (nonatomic, retain) id<IJKMediaUrlOpenDelegate> liveOpenDelegate;

@property (nonatomic, retain) id<IJKMediaNativeInvokeDelegate> nativeInvokeDelegate;

- (void)didShutdown;

#pragma mark KVO properties
/// 播放及媒体信息监听
@property (nonatomic, readonly) IJKFFMonitor *monitor;

@end

#define IJK_FF_IO_TYPE_READ (1)
void IJKFFIOStatDebugCallback(const char *url, int type, int bytes);
void IJKFFIOStatRegister(void (*cb)(const char *url, int type, int bytes));

void IJKFFIOStatCompleteDebugCallback(const char *url,
                                      int64_t read_bytes, int64_t total_size,
                                      int64_t elpased_time, int64_t total_duration);
void IJKFFIOStatCompleteRegister(void (*cb)(const char *url,
                                            int64_t read_bytes, int64_t total_size,
                                            int64_t elpased_time, int64_t total_duration));
