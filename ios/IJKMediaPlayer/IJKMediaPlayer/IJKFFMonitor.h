/*
 * Copyright (c) 2016 Bilibili
 * Copyright (c) 2016 Zhang Rui <bbcallen@gmail.com>
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


/**
 ijkPlayer mpeg 监视器
 */
@interface IJKFFMonitor : NSObject

- (instancetype)init;

/// 媒体元数据
@property(nonatomic) NSDictionary *mediaMeta;
/// 视频元数据
@property(nonatomic) NSDictionary *videoMeta;
/// 音频元数据
@property(nonatomic) NSDictionary *audioMeta;

/// 时长（毫秒）
@property(nonatomic, readonly) int64_t   duration;   // milliseconds
/// 码率（bit / sec）
@property(nonatomic, readonly) int64_t   bitrate;    // bit / sec
/// 帧率（frame / sec）
@property(nonatomic, readonly) float     fps;        // frame / sec
/// 视频宽
@property(nonatomic, readonly) int       width;      // width
/// 视频长
@property(nonatomic, readonly) int       height;     // height
/// 视频编码解码器
@property(nonatomic, readonly) NSString *vcodec;     // video codec
/// 音频编码解码器
@property(nonatomic, readonly) NSString *acodec;     // audio codec
/// 采样率
@property(nonatomic, readonly) int       sampleRate;
@property(nonatomic, readonly) int64_t   channelLayout;

/// 视频解码器
@property(nonatomic) NSString *vdecoder;

/// TCP 错误码
@property(nonatomic) int       tcpError;
/// 远程 IP
@property(nonatomic) NSString *remoteIp;

/// HTTP 错误码
@property(nonatomic) int       httpError;
/// HTTP URL
@property(nonatomic) NSString *httpUrl;
/// HTTP 主机地址
@property(nonatomic) NSString *httpHost;
/// HTTP 响应码
@property(nonatomic) int       httpCode;
@property(nonatomic) int64_t   httpOpenTick;
@property(nonatomic) int64_t   httpSeekTick;
@property(nonatomic) int       httpOpenCount;
@property(nonatomic) int       httpSeekCount;
@property(nonatomic) int64_t   lastHttpOpenDuration;
@property(nonatomic) int64_t   lastHttpSeekDuration;

@property(nonatomic) int64_t   prepareStartTick;
@property(nonatomic) int64_t   prepareDuration;
@property(nonatomic) int64_t   firstVideoFrameLatency;
@property(nonatomic) int64_t   lastPrerollStartTick;
@property(nonatomic) int64_t   lastPrerollDuration;

@end
