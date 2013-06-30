/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package io.humble.video;
import io.humble.ferry.*;
/**
 * Represents settable properties that effect how Humble Video objects 
 *  
 * operate.  
 * <p>  
 * For example, setting the &quot;b&quot; property on an  
 * {@link IStreamCoder} sets the bit-rate the coder will attempt  
 * to encode at.  
 * </p>  
 */
public class IProperty extends RefCounted {
  // JNIHelper.swg: Start generated code
  // >>>>>>>>>>>>>>>>>>>>>>>>>>>
  /**
   * This method is only here to use some references and remove
   * a Eclipse compiler warning.
   */
  @SuppressWarnings("unused")
  private void noop()
  {
    IBuffer.make(null, 1);
  }
   
  private volatile long swigCPtr;

  /**
   * Internal Only.
   */
  protected IProperty(long cPtr, boolean cMemoryOwn) {
    super(VideoJNI.SWIGIPropertyUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }
  
  /**
   * Internal Only.
   */
  protected IProperty(long cPtr, boolean cMemoryOwn,
      java.util.concurrent.atomic.AtomicLong ref)
  {
    super(VideoJNI.SWIGIPropertyUpcast(cPtr),
     cMemoryOwn, ref);
    swigCPtr = cPtr;
  }
    
  /**
   * Internal Only.  Not part of public API.
   *
   * Get the raw value of the native object that obj is proxying for.
   *   
   * @param obj The java proxy object for a native object.
   * @return The raw pointer obj is proxying for.
   */
  public static long getCPtr(IProperty obj) {
    if (obj == null) return 0;
    return obj.getMyCPtr();
  }

  /**
   * Internal Only.  Not part of public API.
   *
   * Get the raw value of the native object that we're proxying for.
   *   
   * @return The raw pointer we're proxying for.
   */  
  public long getMyCPtr() {
    if (swigCPtr == 0) throw new IllegalStateException("underlying native object already deleted");
    return swigCPtr;
  }
  
  /**
   * Create a new IProperty object that is actually referring to the
   * exact same underlying native object.
   *
   * @return the new Java object.
   */
  @Override
  public IProperty copyReference() {
    if (swigCPtr == 0)
      return null;
    else
      return new IProperty(swigCPtr, swigCMemOwn, getJavaRefCount());
  }

  /**
   * Compares two values, returning true if the underlying objects in native code are the same object.
   *
   * That means you can have two different Java objects, but when you do a comparison, you'll find out
   * they are the EXACT same object.
   *
   * @return True if the underlying native object is the same.  False otherwise.
   */
  public boolean equals(Object obj) {
    boolean equal = false;
    if (obj instanceof IProperty)
      equal = (((IProperty)obj).swigCPtr == this.swigCPtr);
    return equal;
  }
  
  /**
   * Get a hashable value for this object.
   *
   * @return the hashable value.
   */
  public int hashCode() {
     return (int)swigCPtr;
  }
  
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<
  // JNIHelper.swg: End generated code
  

/**
 * Get the name for this property.  
 * @return	the name.  
 */
  public String getName() {
    return VideoJNI.IProperty_getName(swigCPtr, this);
  }

/**
 * Get the (English) help string for this property.  
 * @return	the help string  
 */
  public String getHelp() {
    return VideoJNI.IProperty_getHelp(swigCPtr, this);
  }

/**
 * Get any sub-unit this option or constant belongs to.  
 * @return	the unit, or null if none.  
 */
  public String getUnit() {
    return VideoJNI.IProperty_getUnit(swigCPtr, this);
  }

/**
 * Get the underlying native type of this property.  
 * @return	the type  
 */
  public IProperty.Type getType() {
    return IProperty.Type.swigToEnum(VideoJNI.IProperty_getType(swigCPtr, this));
  }

/**
 * Get any set flags (a bitmask) for this option.  
 * @return	the flags  
 */
  public int getFlags() {
    return VideoJNI.IProperty_getFlags(swigCPtr, this);
  }

/**
 * Get the default setting this flag would have it not set.  
 * @return	the default  
 */
  public long getDefault() {
    return VideoJNI.IProperty_getDefault(swigCPtr, this);
  }

/**
 * Get the default setting this flag would have it not set.  
 * @return	the default  
 */
  public double getDefaultAsDouble() {
    return VideoJNI.IProperty_getDefaultAsDouble(swigCPtr, this);
  }

/**
 * If this IProperty is of the type {@link Type#PROPERTY_FLAGS}, this 
 * method will  
 * tell you how many different flag settings it takes.  
 * @return	Number of flag settings, or <0 if not a FLAGS value  
 */
  public int getNumFlagSettings() {
    return VideoJNI.IProperty_getNumFlagSettings(swigCPtr, this);
  }

/**
 * If this IProperty is of the type {@link Type#PROPERTY_FLAGS}, this 
 * method will  
 * give you another IProperty representing a constant setting for that 
 * flag.  
 * @param	position The position number for the flag; Must be in range 
 *		 0 <= position <= #getNumFlagSettings().  
 * @return	An IProperty object for the flag setting, or null if not 
 *		 available.  
 */
  public IProperty getFlagConstant(int position) {
    long cPtr = VideoJNI.IProperty_getFlagConstant__SWIG_0(swigCPtr, this, position);
    return (cPtr == 0) ? null : new IProperty(cPtr, false);
  }

/**
 * If this IProperty is of the type {@link Type#PROPERTY_FLAGS}, this 
 * method will  
 * give you another IProperty representing a constant setting for that 
 * flag.  
 * @param	name The name of the constant.  
 * @return	An IProperty object for the flag setting, or null if not 
 *		 available.  
 */
  public IProperty getFlagConstant(String name) {
    long cPtr = VideoJNI.IProperty_getFlagConstant__SWIG_1(swigCPtr, this, name);
    return (cPtr == 0) ? null : new IProperty(cPtr, false);
  }

  public enum Type {
  /**
   * The different type of options that are supported by Humble Video. 
   *
   * Well, actually by FFMPEG, but you get the idea.
   */
    PROPERTY_FLAGS,
    PROPERTY_INT,
    PROPERTY_INT64,
    PROPERTY_DOUBLE,
    PROPERTY_FLOAT,
    PROPERTY_STRING,
    PROPERTY_RATIONAL,
    PROPERTY_BINARY,
    PROPERTY_CONST(VideoJNI.IProperty_PROPERTY_CONST_get()),
    PROPERTY_IMAGE_SIZE(VideoJNI.IProperty_PROPERTY_IMAGE_SIZE_get()),
    PROPERTY_PIXEL_FMT(VideoJNI.IProperty_PROPERTY_PIXEL_FMT_get()),
    PROPERTY_SAMPLE_FMT(VideoJNI.IProperty_PROPERTY_SAMPLE_FMT_get()),
    PROPERTY_UNKNOWN(VideoJNI.IProperty_PROPERTY_UNKNOWN_get());

    public final int swigValue() {
      return swigValue;
    }

    public static Type swigToEnum(int swigValue) {
      Type[] swigValues = Type.class.getEnumConstants();
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (Type swigEnum : swigValues)
        if (swigEnum.swigValue == swigValue)
          return swigEnum;
      throw new IllegalArgumentException("No enum " + Type.class + " with value " + swigValue);
    }

    @SuppressWarnings("unused")
    private Type() {
      this.swigValue = SwigNext.next++;
    }

    @SuppressWarnings("unused")
    private Type(int swigValue) {
      this.swigValue = swigValue;
      SwigNext.next = swigValue+1;
    }

    @SuppressWarnings("unused")
    private Type(Type swigEnum) {
      this.swigValue = swigEnum.swigValue;
      SwigNext.next = this.swigValue+1;
    }

    private final int swigValue;

    private static class SwigNext {
      private static int next = 0;
    }
  }

  public enum Flags {
    FLAG_ENCODING_PARAM(VideoJNI.IProperty_FLAG_ENCODING_PARAM_get()),
    FLAG_DECODING_PARAM(VideoJNI.IProperty_FLAG_DECODING_PARAM_get()),
    FLAG_METADATA(VideoJNI.IProperty_FLAG_METADATA_get()),
    FLAG_AUDIO_PARAM(VideoJNI.IProperty_FLAG_AUDIO_PARAM_get()),
    FLAG_VIDEO_PARAM(VideoJNI.IProperty_FLAG_VIDEO_PARAM_get()),
    FLAG_SUBTITLE_PARAM(VideoJNI.IProperty_FLAG_SUBTITLE_PARAM_get()),
    FLAG_FILTERING_PARAM(VideoJNI.IProperty_FLAG_FILTERING_PARAM_get());

    public final int swigValue() {
      return swigValue;
    }

    public static Flags swigToEnum(int swigValue) {
      Flags[] swigValues = Flags.class.getEnumConstants();
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (Flags swigEnum : swigValues)
        if (swigEnum.swigValue == swigValue)
          return swigEnum;
      throw new IllegalArgumentException("No enum " + Flags.class + " with value " + swigValue);
    }

    @SuppressWarnings("unused")
    private Flags() {
      this.swigValue = SwigNext.next++;
    }

    @SuppressWarnings("unused")
    private Flags(int swigValue) {
      this.swigValue = swigValue;
      SwigNext.next = swigValue+1;
    }

    @SuppressWarnings("unused")
    private Flags(Flags swigEnum) {
      this.swigValue = swigEnum.swigValue;
      SwigNext.next = this.swigValue+1;
    }

    private final int swigValue;

    private static class SwigNext {
      private static int next = 0;
    }
  }

  public enum Search {
  /**
   * How to search options when looking for different values.
   * Do not search child options
   */
    PROPERTY_SEARCH_DEFAULT(VideoJNI.IProperty_PROPERTY_SEARCH_DEFAULT_get()),
  /**
   * Search children first
   */
    PROPERTY_SEARCH_CHILDREN(VideoJNI.IProperty_PROPERTY_SEARCH_CHILDREN_get());

    public final int swigValue() {
      return swigValue;
    }

    public static Search swigToEnum(int swigValue) {
      Search[] swigValues = Search.class.getEnumConstants();
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (Search swigEnum : swigValues)
        if (swigEnum.swigValue == swigValue)
          return swigEnum;
      throw new IllegalArgumentException("No enum " + Search.class + " with value " + swigValue);
    }

    @SuppressWarnings("unused")
    private Search() {
      this.swigValue = SwigNext.next++;
    }

    @SuppressWarnings("unused")
    private Search(int swigValue) {
      this.swigValue = swigValue;
      SwigNext.next = swigValue+1;
    }

    @SuppressWarnings("unused")
    private Search(Search swigEnum) {
      this.swigValue = swigEnum.swigValue;
      SwigNext.next = this.swigValue+1;
    }

    private final int swigValue;

    private static class SwigNext {
      private static int next = 0;
    }
  }

}