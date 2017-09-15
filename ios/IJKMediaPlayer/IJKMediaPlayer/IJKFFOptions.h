/*
 * IJKFFOptions.h
 *
 * Copyright (c) 2013-2015 Bilibili
 * Copyright (c) 2013-2015 Zhang Rui <bbcallen@gmail.com>
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
 选项类别
 
 - kIJKFFOptionCategoryFormat: 格式选项
 - kIJKFFOptionCategoryCodec: 编码解码器选项
 - kIJKFFOptionCategorySws:
 - kIJKFFOptionCategoryPlayer: 播放器选项
 - kIJKFFOptionCategorySwr:
 */
typedef enum IJKFFOptionCategory {
	/// 格式选项
    kIJKFFOptionCategoryFormat = 1,
	/// 编码解码器选项
    kIJKFFOptionCategoryCodec  = 2,
    kIJKFFOptionCategorySws    = 3,
	/// 播放器选项
    kIJKFFOptionCategoryPlayer = 4,
    kIJKFFOptionCategorySwr    = 5,
} IJKFFOptionCategory;

// for codec option 'skip_loop_filter' and 'skip_frame'
/**
 丢帧策略
 
 - IJK_AVDISCARD_NONE: 不丢帧
 - IJK_AVDISCARD_DEFAULT: 默认，丢弃无效包
 - IJK_AVDISCARD_NONREF: 丢弃非参考帧（I帧）
 - IJK_AVDISCARD_BIDIR: 丢弃B帧
 - IJK_AVDISCARD_NONKEY: 丢弃除关键帧以外的帧，如 B、P 帧
 - IJK_AVDISCARD_ALL: 丢弃所有的帧
 */
typedef enum IJKAVDiscard {
    /* We leave some space between them for extensions (drop some
	 * keyframes for intra-only or drop just some bidir frames). */
	/// 不丢帧
    IJK_AVDISCARD_NONE    =-16, ///< discard nothing
	/// 默认，丢弃无效包
    IJK_AVDISCARD_DEFAULT =  0, ///< discard useless packets like 0 size packets in avi
	/// 丢弃非参考帧（I帧）
    IJK_AVDISCARD_NONREF  =  8, ///< discard all non reference
	/// 丢弃B帧
    IJK_AVDISCARD_BIDIR   = 16, ///< discard all bidirectional frames
	/// 丢弃除关键帧以外的帧，如 B、P 帧
    IJK_AVDISCARD_NONKEY  = 32, ///< discard all frames except keyframes
	/// 丢弃所有的帧
    IJK_AVDISCARD_ALL     = 48, ///< discard all
} IJKAVDiscard;

struct IjkMediaPlayer;

@interface IJKFFOptions : NSObject

/**
 初始化为默认配置

 @return 默认配置
 */
+ (IJKFFOptions *)optionsByDefault;


/**
 应用到播放器

 @param mediaPlayer IjkMediaPlayer 结构体
 */
- (void)applyTo:(struct IjkMediaPlayer *)mediaPlayer;


/**
 配置选项

 @param value 字符串值
 @param key 键
 @param category 选项类别
 */
- (void)setOptionValue:(NSString *)value
                forKey:(NSString *)key
            ofCategory:(IJKFFOptionCategory)category;

/**
 配置选项

 @param value 整型值
 @param key 键
 @param category 选项类别
 */
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

/// 是否显示浮层
@property(nonatomic) BOOL showHudView;

@end
