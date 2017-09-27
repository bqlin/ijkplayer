/*
 * IJKMediaPlayback.h
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

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


/**
 视频拉伸模式

 - IJKMPMovieScalingModeNone: 无拉伸
 - IJKMPMovieScalingModeAspectFit: 适应，等比拉伸直到任意一边贴合
 - IJKMPMovieScalingModeAspectFill: 填充，等比拉伸直到填满
 - IJKMPMovieScalingModeFill: 拉伸，拉伸宽高以填满
 */
typedef NS_ENUM(NSInteger, IJKMPMovieScalingMode) {
	/// 无拉伸
    IJKMPMovieScalingModeNone,       // No scaling
	/// 适应，等比拉伸直到任意一边贴合
    IJKMPMovieScalingModeAspectFit,  // Uniform scale until one dimension fits
	/// 填充，等比拉伸直到填满
    IJKMPMovieScalingModeAspectFill, // Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
	/// 拉伸，拉伸宽高以填满
    IJKMPMovieScalingModeFill        // Non-uniform scale. Both render dimensions will exactly match the visible bounds
};


/**
 播放状态

 - IJKMPMoviePlaybackStateStopped: 停止
 - IJKMPMoviePlaybackStatePlaying: 播放
 - IJKMPMoviePlaybackStatePaused: 暂停
 - IJKMPMoviePlaybackStateInterrupted: 中断
 - IJKMPMoviePlaybackStateSeekingForward: 快进
 - IJKMPMoviePlaybackStateSeekingBackward: 快退
 */
typedef NS_ENUM(NSInteger, IJKMPMoviePlaybackState) {
	/// 停止
    IJKMPMoviePlaybackStateStopped,
	/// 播放
    IJKMPMoviePlaybackStatePlaying,
	/// 暂停
    IJKMPMoviePlaybackStatePaused,
	/// 中断
    IJKMPMoviePlaybackStateInterrupted,
	/// 快进
    IJKMPMoviePlaybackStateSeekingForward,
	/// 快退
    IJKMPMoviePlaybackStateSeekingBackward
};


/**
 加载状态

 - IJKMPMovieLoadStateUnknown: 未知
 - IJKMPMovieLoadStatePlayable: 可播放
 - IJKMPMovieLoadStatePlaythroughOK: 流畅播放
 - IJKMPMovieLoadStateStalled: 加载中
 */
typedef NS_OPTIONS(NSUInteger, IJKMPMovieLoadState) {
	/// 未知
    IJKMPMovieLoadStateUnknown        = 0,
	/// 可播放
    IJKMPMovieLoadStatePlayable       = 1 << 0,
	/// 流畅播放
    IJKMPMovieLoadStatePlaythroughOK  = 1 << 1, // Playback will be automatically started in this state when shouldAutoplay is YES
	/// 加载中
    IJKMPMovieLoadStateStalled        = 1 << 2, // Playback will be automatically paused in this state, if started
};


/**
 结束原因

 - IJKMPMovieFinishReasonPlaybackEnded: 播放结束
 - IJKMPMovieFinishReasonPlaybackError: 播放错误
 - IJKMPMovieFinishReasonUserExited: 用户退出
 */
typedef NS_ENUM(NSInteger, IJKMPMovieFinishReason) {
	/// 播放结束
    IJKMPMovieFinishReasonPlaybackEnded,
	/// 播放错误
    IJKMPMovieFinishReasonPlaybackError,
	/// 用户退出
    IJKMPMovieFinishReasonUserExited
};

// -----------------------------------------------------------------------------
// Thumbnails


/**
 时间选项

 - IJKMPMovieTimeOptionNearestKeyFrame: 关键帧附近
 - IJKMPMovieTimeOptionExact: 精确
 */
typedef NS_ENUM(NSInteger, IJKMPMovieTimeOption) {
	/// 关键帧附近
    IJKMPMovieTimeOptionNearestKeyFrame,
	/// 精确
    IJKMPMovieTimeOptionExact
};

@protocol IJKMediaPlayback;

#pragma mark IJKMediaPlayback

/// 播放方法协议
@protocol IJKMediaPlayback <NSObject>

/**
 就绪播放
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
 是否播放

 @return 是否在播放
 */
- (BOOL)isPlaying;
/**
 销毁播放器
 */
- (void)shutdown;
/**
 后台暂停播放

 @param pause 后台暂停播放
 */
- (void)setPauseInBackground:(BOOL)pause;

/// 媒体视图
@property(nonatomic, readonly)  UIView *view;
/// 当前播放时间
@property(nonatomic)            NSTimeInterval currentPlaybackTime;
/// 媒体时长
@property(nonatomic, readonly)  NSTimeInterval duration;
/// 可播放时长
@property(nonatomic, readonly)  NSTimeInterval playableDuration;
/// 缓冲进度
@property(nonatomic, readonly)  NSInteger bufferingProgress;

/// 是否就绪播放
@property(nonatomic, readonly)  BOOL isPreparedToPlay;
/// 播放状体啊
@property(nonatomic, readonly)  IJKMPMoviePlaybackState playbackState;
/// 加载状态
@property(nonatomic, readonly)  IJKMPMovieLoadState loadState;

/// 传输字节数
@property(nonatomic, readonly) int64_t numberOfBytesTransferred;

/// 原始尺寸
@property(nonatomic, readonly) CGSize naturalSize;
/// 拉伸模式
@property(nonatomic) IJKMPMovieScalingMode scalingMode;
/// 是否自动播放
@property(nonatomic) BOOL shouldAutoplay;

/// 是否允许媒体 Airplay
@property (nonatomic) BOOL allowsMediaAirPlay;
/// 是否允许弹幕媒体 Airplay
@property (nonatomic) BOOL isDanmakuMediaAirPlay;
/// Airplay 是否激活
@property (nonatomic, readonly) BOOL airPlayMediaActive;

/// 播放速率
@property (nonatomic) float playbackRate;
/// 播放音量
@property (nonatomic) float playbackVolume;

/// 当前时间截图
- (UIImage *)thumbnailImageAtCurrentTime;

#pragma mark Notifications

#ifdef __cplusplus
#define IJK_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define IJK_EXTERN extern __attribute__((visibility ("default")))
#endif

// -----------------------------------------------------------------------------
//  MPMediaPlayback.h

// Posted when the prepared state changes of an object conforming to the MPMediaPlayback protocol changes.
// This supersedes MPMoviePlayerContentPreloadDidFinishNotification.
/// 就绪状态变更通知
IJK_EXTERN NSString *const IJKMPMediaPlaybackIsPreparedToPlayDidChangeNotification;

// -----------------------------------------------------------------------------
//  MPMoviePlayerController.h
//  Movie Player Notifications

// Posted when the scaling mode changes.
/// 视频拉伸模式变更通知
IJK_EXTERN NSString* const IJKMPMoviePlayerScalingModeDidChangeNotification;

// Posted when movie playback ends or a user exits playback.
/// 播放结束通知
IJK_EXTERN NSString* const IJKMPMoviePlayerPlaybackDidFinishNotification;
/// 播放结束原因通知
IJK_EXTERN NSString* const IJKMPMoviePlayerPlaybackDidFinishReasonUserInfoKey; // NSNumber (IJKMPMovieFinishReason)

// Posted when the playback state changes, either programatically or by the user.
/// 播放状态变更通知
IJK_EXTERN NSString* const IJKMPMoviePlayerPlaybackStateDidChangeNotification;

// Posted when the network load state changes.
/// 加载状态变更通知
IJK_EXTERN NSString* const IJKMPMoviePlayerLoadStateDidChangeNotification;

// Posted when the movie player begins or ends playing video via AirPlay.
/// AirPlay 状态变更通知
IJK_EXTERN NSString* const IJKMPMoviePlayerIsAirPlayVideoActiveDidChangeNotification;

// -----------------------------------------------------------------------------
// Movie Property Notifications

// Calling -prepareToPlay on the movie player will begin determining movie properties asynchronously.
// These notifications are posted when the associated movie property becomes available.
/// 视频尺寸可用通知
IJK_EXTERN NSString* const IJKMPMovieNaturalSizeAvailableNotification;

// -----------------------------------------------------------------------------
//  Extend Notifications

/// 视频解码开启通知
IJK_EXTERN NSString *const IJKMPMoviePlayerVideoDecoderOpenNotification;
/// 首帧视频渲染通知
IJK_EXTERN NSString *const IJKMPMoviePlayerFirstVideoFrameRenderedNotification;
/// 首帧音频渲染通知
IJK_EXTERN NSString *const IJKMPMoviePlayerFirstAudioFrameRenderedNotification;

/// 跳转结束通知
IJK_EXTERN NSString *const IJKMPMoviePlayerDidSeekCompleteNotification;
/// 跳转目标键
IJK_EXTERN NSString *const IJKMPMoviePlayerDidSeekCompleteTargetKey;
/// 跳转错误键
IJK_EXTERN NSString *const IJKMPMoviePlayerDidSeekCompleteErrorKey;
/// 精确跳转当前位置
IJK_EXTERN NSString *const IJKMPMoviePlayerDidAccurateSeekCompleteCurPos;
/// 精确跳转完成通知
IJK_EXTERN NSString *const IJKMPMoviePlayerAccurateSeekCompleteNotification;

@end

#pragma mark IJKMediaUrlOpenDelegate

// Must equal to the defination in ijkavformat/ijkavformat.h
/// 媒体事件
typedef NS_ENUM(NSInteger, IJKMediaEvent) {

    // Notify Events
    IJKMediaEvent_WillHttpOpen         = 1,       // attr: url
    IJKMediaEvent_DidHttpOpen          = 2,       // attr: url, error, http_code
    IJKMediaEvent_WillHttpSeek         = 3,       // attr: url, offset
    IJKMediaEvent_DidHttpSeek          = 4,       // attr: url, offset, error, http_code
    // Control Message
    IJKMediaCtrl_WillTcpOpen           = 0x20001, // IJKMediaUrlOpenData: no args
    IJKMediaCtrl_DidTcpOpen            = 0x20002, // IJKMediaUrlOpenData: error, family, ip, port, fd
    IJKMediaCtrl_WillHttpOpen          = 0x20003, // IJKMediaUrlOpenData: url, segmentIndex, retryCounter
    IJKMediaCtrl_WillLiveOpen          = 0x20005, // IJKMediaUrlOpenData: url, retryCounter
    IJKMediaCtrl_WillConcatSegmentOpen = 0x20007, // IJKMediaUrlOpenData: url, segmentIndex, retryCounter
};

#define IJKMediaEventAttrKey_url            @"url"
#define IJKMediaEventAttrKey_host           @"host"
#define IJKMediaEventAttrKey_error          @"error"
#define IJKMediaEventAttrKey_time_of_event  @"time_of_event"
#define IJKMediaEventAttrKey_http_code      @"http_code"
#define IJKMediaEventAttrKey_offset         @"offset"

// event of IJKMediaUrlOpenEvent_xxx
@interface IJKMediaUrlOpenData: NSObject

- (id)initWithUrl:(NSString *)url
            event:(IJKMediaEvent)event
     segmentIndex:(int)segmentIndex
     retryCounter:(int)retryCounter;

/// 媒体事件
@property(nonatomic, readonly) IJKMediaEvent event;
/// 段索引
@property(nonatomic, readonly) int segmentIndex;
/// 重试次数
@property(nonatomic, readonly) int retryCounter;

@property(nonatomic, copy) NSString *url;
@property(nonatomic, assign) int fd;
@property(nonatomic, strong) NSString *msg;
@property(nonatomic) int error; // set a negative value to indicate an error has occured.
@property(nonatomic, getter=isHandled)    BOOL handled;     // auto set to YES if url changed
@property(nonatomic, getter=isUrlChanged) BOOL urlChanged;  // auto set to YES by url changed

@end

@protocol IJKMediaUrlOpenDelegate <NSObject>

- (void)willOpenUrl:(IJKMediaUrlOpenData *) urlOpenData;

@end

@protocol IJKMediaNativeInvokeDelegate <NSObject>

- (int)invoke:(IJKMediaEvent)event attributes:(NSDictionary *)attributes;

@end
