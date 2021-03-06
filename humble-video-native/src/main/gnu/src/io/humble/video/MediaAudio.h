/*******************************************************************************
 * Copyright (c) 2014, Andrew "Art" Clarke.  All rights reserved.
 *   
 * This file is part of Humble-Video.
 *
 * Humble-Video is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Humble-Video is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Humble-Video.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************/
/*
 * Audio.h
 *
 *  Created on: Jul 10, 2013
 *      Author: aclarke
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <io/humble/ferry/Buffer.h>
#include <io/humble/video/HumbleVideo.h>
#include <io/humble/video/MediaRaw.h>

namespace io {
namespace humble {
namespace video {

/**
 * A class that defines meta-data about audio channels and layouts.
 */
class VS_API_HUMBLEVIDEO AudioChannel : public io::humble::ferry::RefCounted
{
  // This object is ALL static ALL the time.
VS_JNIUTILS_REFCOUNTED_OBJECT_PRIVATE_MAKE(AudioChannel)
  ;
public:

  /**
   * Flags for each type of audio channel that can be in multi-channel audio.
   */
  typedef enum Type
  {
    CH_UNKNOWN = 0,
    CH_FRONT_LEFT = AV_CH_FRONT_LEFT,
    CH_FRONT_RIGHT = AV_CH_FRONT_RIGHT,
    CH_FRONT_CENTER = AV_CH_FRONT_CENTER,
    CH_LOW_FREQUENCY = AV_CH_LOW_FREQUENCY,
    CH_BACK_LEFT = AV_CH_BACK_LEFT,
    CH_BACK_RIGHT = AV_CH_BACK_RIGHT,
    CH_FRONT_LEFT_OF_CENTER = AV_CH_FRONT_LEFT_OF_CENTER,
    CH_FRONT_RIGHT_OF_CENTER = AV_CH_FRONT_RIGHT_OF_CENTER,
    CH_BACK_CENTER = AV_CH_BACK_CENTER,
    CH_SIDE_LEFT = AV_CH_SIDE_LEFT,
    CH_SIDE_RIGHT = AV_CH_SIDE_RIGHT,
    CH_TOP_CENTER = AV_CH_TOP_CENTER,
    CH_TOP_FRONT_LEFT = AV_CH_TOP_FRONT_LEFT,
    CH_TOP_FRONT_CENTER = AV_CH_TOP_FRONT_CENTER,
    CH_TOP_FRONT_RIGHT = AV_CH_TOP_FRONT_RIGHT,
    CH_TOP_BACK_LEFT = AV_CH_TOP_BACK_LEFT,
    CH_TOP_BACK_CENTER = AV_CH_TOP_BACK_CENTER,
    CH_TOP_BACK_RIGHT = AV_CH_TOP_BACK_RIGHT,
    CH_STEREO_LEFT = AV_CH_STEREO_LEFT,
    CH_STEREO_RIGHT = AV_CH_STEREO_RIGHT,
    CH_WIDE_LEFT = AV_CH_WIDE_LEFT,
    CH_WIDE_RIGHT = AV_CH_WIDE_RIGHT,
    CH_SURROUND_DIRECT_LEFT = AV_CH_SURROUND_DIRECT_LEFT,
    CH_SURROUND_DIRECT_RIGHT = AV_CH_SURROUND_DIRECT_RIGHT,
    CH_LOW_FREQUENCY_2 = AV_CH_LOW_FREQUENCY_2,
  } Type;

  /**
   * Different layouts of audio channels. The
   * value of these flags are ultimately a
   * bitmask of different {#Type} flags.
   */
  typedef enum Layout
  {
    CH_LAYOUT_UNKNOWN = 0,
    CH_LAYOUT_NATIVE = AV_CH_LAYOUT_NATIVE,
    CH_LAYOUT_MONO = AV_CH_LAYOUT_MONO,
    CH_LAYOUT_STEREO = AV_CH_LAYOUT_STEREO,
    CH_LAYOUT_2POINT1 = AV_CH_LAYOUT_2POINT1,
    CH_LAYOUT_2_1 = AV_CH_LAYOUT_2_1,
    CH_LAYOUT_SURROUND = AV_CH_LAYOUT_SURROUND,
    CH_LAYOUT_3POINT1 = AV_CH_LAYOUT_3POINT1,
    CH_LAYOUT_4POINT0 = AV_CH_LAYOUT_4POINT0,
    CH_LAYOUT_4POINT1 = AV_CH_LAYOUT_4POINT1,
    CH_LAYOUT_2_2 = AV_CH_LAYOUT_2_2,
    CH_LAYOUT_QUAD = AV_CH_LAYOUT_QUAD,
    CH_LAYOUT_5POINT0 = AV_CH_LAYOUT_5POINT0,
    CH_LAYOUT_5POINT1 = AV_CH_LAYOUT_5POINT1,
    CH_LAYOUT_5POINT0_BACK = AV_CH_LAYOUT_5POINT0_BACK,
    CH_LAYOUT_5POINT1_BACK = AV_CH_LAYOUT_5POINT1_BACK,
    CH_LAYOUT_6POINT0 = AV_CH_LAYOUT_6POINT0,
    CH_LAYOUT_6POINT0_FRONT = AV_CH_LAYOUT_6POINT0_FRONT,
    CH_LAYOUT_HEXAGONAL = AV_CH_LAYOUT_HEXAGONAL,
    CH_LAYOUT_6POINT1 = AV_CH_LAYOUT_6POINT1,
    CH_LAYOUT_6POINT1_BACK = AV_CH_LAYOUT_6POINT1_BACK,
    CH_LAYOUT_6POINT1_FRONT = AV_CH_LAYOUT_6POINT1_FRONT,
    CH_LAYOUT_7POINT0 = AV_CH_LAYOUT_7POINT0,
    CH_LAYOUT_7POINT0_FRONT = AV_CH_LAYOUT_7POINT0_FRONT,
    CH_LAYOUT_7POINT1 = AV_CH_LAYOUT_7POINT1,
    CH_LAYOUT_7POINT1_WIDE = AV_CH_LAYOUT_7POINT1_WIDE,
    CH_LAYOUT_7POINT1_WIDE_BACK = AV_CH_LAYOUT_7POINT1_WIDE_BACK,
    CH_LAYOUT_OCTAGONAL = AV_CH_LAYOUT_OCTAGONAL,
    CH_LAYOUT_STEREO_DOWNMIX = AV_CH_LAYOUT_STEREO_DOWNMIX,
  } Layout;

  /**
   * Return a channel layout bitmask that matches name, or 0 if no match is found.
   *
   * name can be one or several of the following notations,
   * separated by '+' or '|':
   * - the name of an usual channel layout (mono, stereo, 4.0, quad, 5.0,
   *   5.0(side), 5.1, 5.1(side), 7.1, 7.1(wide), downmix);
   * - the name of a single channel (FL, FR, FC, LFE, BL, BR, FLC, FRC, BC,
   *   SL, SR, TC, TFL, TFC, TFR, TBL, TBC, TBR, DL, DR);
   * - a number of channels, in decimal, optionally followed by 'c', yielding
   *   the default channel layout for that number of channels (@see
   *   av_get_default_channel_layout);
   * - a channel layout mask, in hexadecimal starting with "0x" (see the
   *   Layout and Channel enums).
   *
   * Example: "stereo+FC" = "2+FC" = "2c+1c" = "0x7"
   */
  static int64_t
  getChannelBitmask(const char* name);

  /**
   *
   * Return a description of a channel bitmask.
   * If numChannels is <= 0, it is guessed from the layout.
   * Note to C/C++ callers. You must call free() on the returned value.
   */
  static char*
  getChannelLayoutString(int32_t numChannels, int64_t layout);
#ifndef SWIG
  static void freeString(char* str);
#endif

#ifdef SWIG
  %newobject getChannelLayoutString(int32_t, int64_t);
  %typemap(newfree) char * "av_free($1);";
#endif

  /**
   * Return the number of channels in the channel layout.
   */
  static int32_t
  getNumChannelsInLayout(Layout layout);

  /**
   * Return default channel layout for a given number of channels.
   */
  static Layout
  getDefaultLayout(int numChannels);

  /**
   * Get the index of a channel in channel_layout.
   *
   * <p>
   * Use this method to find out which index into channel data corresponds
   * to the channel you care about. The way you use this differs depending
   * on whether your audio is packed or planar.  To illustrate, let's assume
   * you have CH_LAYOUT_STEREO audio, and you ask for the index of CH_FRONT_LEFT,
   * and we return 1 (indexes are zero based).
   * </p><p>
   * If packed, then audio is laid out in one big buffer as "RLRLRLRLRLRLRLRL" audio,
   * and every 2nd (1+1) sample is the left channel
   * </p><p>
   * If planar, then audio is out in two buffer as "RRRRRRRR" and "LLLLLLLL", and the
   * second plan (1+1) is the left channel.
   * </p>
   *
   * @param channel a channel layout describing exactly one channel which must be
   *                present in channel_layout.
   *
   * @return index of channel in channel_layout on success, a negative AVERROR
   *         on error.
   */
  static int32_t
  getIndexOfChannelInLayout(Layout layout, Type channel);

  /**
   * Get the channel with the given index in channel_layout.
   */
  static Type
  getChannelFromLayoutAtIndex(Layout layout, int32_t index);

  /**
   * Get the name of a given channel.
   *
   * @return channel name on success, NULL on error.
   */
  static const char *
  getChannelName(Type channel);

  /**
   * Get the description of a given channel.
   *
   * @param channel  a channel layout with a single channel
   * @return  channel description on success, NULL on error
   */
  static const char *
  getChannelDescription(Type channel);

  /**
   * Get the value and name of a standard channel layout.
   *
   * @param[in]  index   index in an internal list, starting at 0
   * @param[out] layout  channel layout mask
   * @param[out] name    name of the layout
   * @return  0  if the layout exists,
   *          <0 if index is beyond the limits
   */
  static const char*
  getLayoutName(Layout layout);

protected:
  AudioChannel() {};
  virtual
  ~AudioChannel() {};
};

/**
 * A class that defines metadata about audio formats.
 */
class VS_API_HUMBLEVIDEO AudioFormat : public virtual io::humble::ferry::RefCounted
{

public:
  /**
   * The format we use to represent audio.
   */
  typedef enum Type
  {
    /** No format */
    SAMPLE_FMT_NONE = AV_SAMPLE_FMT_NONE,
    /** unsigned 8 bits */
    SAMPLE_FMT_U8 = AV_SAMPLE_FMT_U8,
    /** signed 16 bits */
    SAMPLE_FMT_S16 = AV_SAMPLE_FMT_S16,
    /** signed 32 bits */
    SAMPLE_FMT_S32 = AV_SAMPLE_FMT_S32,
    /** float */
    SAMPLE_FMT_FLT = AV_SAMPLE_FMT_FLT,
    /** double */
    SAMPLE_FMT_DBL = AV_SAMPLE_FMT_DBL,

    /** unsigned 8 bits, planar */
    SAMPLE_FMT_U8P = AV_SAMPLE_FMT_U8P,
    /** signed 16 bits, planar */
    SAMPLE_FMT_S16P = AV_SAMPLE_FMT_S16P,
    /** signed 32 bits, planar */
    SAMPLE_FMT_S32P = AV_SAMPLE_FMT_S32P,
    /** float, planar */
    SAMPLE_FMT_FLTP = AV_SAMPLE_FMT_FLTP,
    /** double, planar */
    SAMPLE_FMT_DBLP = AV_SAMPLE_FMT_DBLP,
  } Type;
  /**
   * Return the name of format, or NULL if format is not
   * recognized.
   */
  static const char*
  getName(Type format);

  /**
   * Return a sample format corresponding to name, or SAMPLE_FMT_NONE
   * on error.
   */
  static Type
  getFormat(const char* name);

  /**
   * Return the planar<->packed alternative form of the given sample format, or
   * SAMPLE_FMT_NONE on error. If the passed sample_fmt is already in the
   * requested planar/packed format, the format returned is the same as the
   * input.
   */
  static Type
  getAlternateSampleFormat(Type sample_fmt, bool planar);

  /**
   * Get the packed alternative form of the given sample format.
   *
   * If the passed sample_fmt is already in packed format, the format returned is
   * the same as the input.
   *
   * @return  the packed alternative form of the given sample format or
   AV_SAMPLE_FMT_NONE on error.
   */
  static Type
  getPackedSampleFormat(Type sample_fmt);

  /**
   * Get the planar alternative form of the given sample format.
   *
   * If the passed sample_fmt is already in planar format, the format returned is
   * the same as the input.
   *
   * @return  the planar alternative form of the given sample format or
   SAMPLE_FMT_NONE on error.
   */
  static Type
  getPlanarSampleFormat(Type sample_fmt);

  /**
   * Return number of bytes per sample.
   *
   * @param sample_fmt the sample format
   * @return number of bytes per sample or zero if unknown for the given
   * sample format
   */
  static int32_t
  getBytesPerSample(Type sample_fmt);

  /**
   * Check if the sample format is planar.
   *
   * @param sample_fmt the sample format to inspect
   * @return 1 if the sample format is planar, 0 if it is interleaved
   */
  static bool
  isPlanar(Type sample_fmt);

  /**
   * Get the size of a buffer in bytes that would be required to hold the
   * number of samples of audio in the given format and with the given number of channels.
   */
  static int32_t
  getBufferSizeNeeded(int32_t numSamples, int32_t numChannels, Type format);

  /**
   * Get the size of a plane of audio bytes that would be required to hold the
   * number of samples of audio in the given format and with the given number of channels.
   * <p>
   * If format is packed, then this method returns the same number as #getBufferSizeNeeded(int, int, Type).
   * </p>
   */
  static int32_t
  getDataPlaneSizeNeeded(int32_t numSamples, int32_t numChannels, Type format);
protected:
  AudioFormat();
  virtual
  ~AudioFormat();
};

/**
 * Raw audio data.
 * <p>
 * The data described by the sample format is always in native-endian order.
 * </p><p>
 * The floating-point formats are based on full volume being in the range
 * [-1.0, 1.0]. Any values outside this range are beyond full volume level.
 *
 * </p><p>
 * The data layout is as follows:
 * </p><p>
 * For planar sample formats, each audio channel is in a separate data plane,
 * and MediaAudio#getDataLineSize(int) is the buffer size, in bytes, for a single plane. All data
 * planes must be the same size. For packed sample formats, only the first data
 * plane is used, and samples for each channel are interleaved. In this case,
 * MediaAudio#getDataLineSize(int) is the buffer size, in bytes, for the 1 plane.
 * </p>
 */
class VS_API_HUMBLEVIDEO MediaAudio : public MediaSampled
{
  VS_JNIUTILS_REFCOUNTED_OBJECT_PRIVATE_MAKE(MediaAudio)
public:
  /**
   * Create a MediaAudio and the underlying data. Will allocate a buffer to back this data.
   * @param numSamples The number of samples of audio that will be placed in this MediaAudio object.
   * @param sampleRate The sample rate (per second) of this audio.
   * @param channels The number of channels of audio that will be placed in this MediaAudio object.
   * @paray channelLayout The channel layout of audio that will be placed in this MediaAudio object.
   * @param format The format of the audio placed in this MediaAudio object.
   * @return A MediaAudio object, or null on failure.
   */
  static MediaAudio*
  make(int32_t numSamples, int32_t sampleRate, int32_t channels, AudioChannel::Layout channelLayout,
      AudioFormat::Type format);
  /**
   * Create a MediaAudio using the given buffer.
   *
   * Note: that the Buffer.getBufferSize() constraints the max number
   * of samples we can place in here, and HumbleVideo needs to reserve some
   * of the buffer for, um, stuff (assume at least 64 bytes). So #getMaxNumSamples()
   * may not return as many as you think you can fit in here.
   *
   * @param buffer A buffer to back the audio with. If not large enough to hold all the samples (with alignment on 32-bit boundaries if planar),
   *    then an error results.
   * @param numSamples The number of samples of audio that will be placed in this MediaAudio object.
   * @param sampleRate The sample rate (per second) of this audio.
   * @param channels The number of channels of audio that will be placed in this MediaAudio object.
   * @paray channelLayout The channel layout of audio that will be placed in this MediaAudio object.
   * @param format The format of the audio placed in this MediaAudio object.
   *
   * @return A MediaAudio object, or null on failure.
   */
  static MediaAudio*
  make(io::humble::ferry::Buffer *buffer, int32_t numSamples,
      int32_t sampleRate, int32_t channels,
      AudioChannel::Layout channelLayout, AudioFormat::Type format);

  /**
   * Create a MediaAudio by either referencing or copying another MediaAudio.
   * <p>
   * This method is very useful when you want to change some meta-data about MediaAudio (such as
   * changing a timestamp) without effecting other users of the same underlying data.
   * </p>
   * <p>
   * It can also be useful to create a copy of the raw audio data in the buffers in the
   * event you are doing audio manipulation and do not want to effect other people
   * using the audio.
   * </p>
   *
   * @param src MediaAudio to reference
   * @param copy true if we should copy all data. false if we should just gain a reference to the same underlying data in src.
   *
   * @return a MediaAudio object, or null on failure.
   */
  static MediaAudio*
  make(MediaAudio* src, bool copy);

  /**
   * Get any underlying raw data available for this object.
   *
   * @param plane The plane number if getFormat() is Planar (rather than packed) audio.  Pass zero for packed data.
   * @return The raw data, or null if not accessible.
   */
  virtual io::humble::ferry::Buffer*
  getData(int32_t plane);

  /**
   * The total number of bytes in #getData() that represent valid audio data.
   * If #isComplete() returns true, this returns the total number of bytes
   * returned by #getData(int) that are readable from. Otherwise it will
   * return the total number of bytes that are writable to.
   *
   * @return The size in bytes of that plane of audio data.
   */
  virtual int32_t
  getDataPlaneSize(int32_t plane);

  /** Returns the number of data planes in this object. */
  virtual int32_t
  getNumDataPlanes();

  /**
   * @return maximum of samples of #getChannels() #getFormat() audio that can be put in this MediaAudio object.
   */
  virtual int32_t
  getMaxNumSamples();

  /**
   * @return the actual number of samples in this object
   */
  virtual int32_t
  getNumSamples();

  /**
   * Set the number of samples in the buffer. Must not be more than
   * #getMaxNumSamples(). Caller is responsible for making
   * sure buffer actually matches this.
   */
  virtual void
  setNumSamples(int32_t numSamples);

  /**
   * Number of bytes in one sample of one channel of audio in this object.
   */
  virtual int32_t
  getBytesPerSample();

  /**
   * Call this if you modify the samples and are now done.  This
   * updates the pertinent information in the structure.
   *
   * @param complete true if complete; false if not.
   */
  virtual void
  setComplete(bool complete);

  /**
   * Sample rate of audio, or 0 if unknown.
   */
  virtual int32_t
  getSampleRate();
  /**
   * Number of channels of audio in this object.
   */
  virtual int32_t
  getChannels();
  /**
   * Format of audio in this object.
   */
  virtual AudioFormat::Type
  getFormat();
  /**
   * Does this object have complete data? If not, other methods may return unknown.
   */
  virtual bool
  isComplete();
  /**
   * Was this audio decoded from a key packet?
   */
  virtual bool
  isKey();
  /**
   * Is audio laid out in a planar format?
   */
  virtual bool
  isPlanar();
  /**
   * What is the channel layout of the audio in this buffer?
   */
  virtual AudioChannel::Layout
  getChannelLayout();

  /**
   * Returns the minimum next timestamp value that would be expected for audio that
   * follows this packet.
   *
   * For example, if the timestamp of this audio is 1152, the sample rate is 22050,
   * and the timebase is 1/44100, and
   * getNumSamples() returns 576, getNextTimeStamp() will return 2304.
   *
   * @return the minimum timestamp of audio that must follow.
   *
   * @throws InvalidArgument if !isComplete().
   *
   */
//  virtual int64_t getNextTimeStamp() = 0;

  /**
   * Adds input audio to this object, copying up to X number of samples.
   *
   * It does NOT modify input in any way. If this object is !isComplete() then
   * this is equivalent to copying the data into this object. If isComplete() then
   * data will be copied on the end (and the buffers may get expanded).
   *
   * @param input Audio to copy from. Must not be null and must be complete().
   * @param numSamples Number of samples to copy. If 0, then all samples are copied.
   * @param injectSilence If true, and input.getTimeStamp() > this.getNextTimeStamp(),
   *                      then we attempt to inject silence to fill the gap. If false,
   *                      we throw an exception if input is not contiguous to this object.
   *
   * @return Actual # of samples (per channel) copied.
   *
   * @throws InvalidArgument if null inputs, incomplete input audio, or numSamples < 0, or the timebases,
   *                         sample rates, formats, or channel layouts are not the same.
   * @throws InvalidArgument if input.getTimeStamp() < this.getNextTimeStamp()
   * @throws OutOfBoundsException if injectSilence is false and input.getTimeStamp() > this.getNextTimeStamp().
   */
//  virtual int32_t push(MediaAudio* input, int32_t numSamples, bool injectSilence);

  /**
   * "Pops" up to numSamples samples from this object and "pushes" them into output.
   *
   * @param output The audio to copy to. May not be null. If no exception thrown, output will be
   *               complete upon return.
   * @param numSamples The maximum number of samples to copy. If 0, then we attempt to copy
   *                   getNumSamples() to output.
   *
   * @return Actual # of samples (per channel) copied.
   *
   * @throws InvalidArgument if null output or numSamples < 0.
   *
   */
//  virtual int32_t pop(MediaAudio* output, int32_t numSamples);

#ifndef SWIG
  virtual AVFrame* getCtx();
  // Copies data from src into this context, first releasing any memory we have.
  virtual void copy(AVFrame* src, bool complete);
  virtual int64_t logMetadata(char *, size_t);
#endif

protected:
  MediaAudio();
  virtual
  ~MediaAudio();
private:
  static void
  setBufferType(AudioFormat::Type format,
      io::humble::ferry::Buffer* buffer);

  AVFrame* mFrame;
  bool     mComplete;

};

} /* namespace video */
} /* namespace humble */
} /* namespace io */
#endif /* AUDIO_H_ */
