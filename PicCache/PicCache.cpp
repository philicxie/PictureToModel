/*
 * This file is part of the OpenKinect Project. http://www.openkinect.org
 *
 * Copyright (c) 2011 individual OpenKinect contributors. See the CONTRIB file
 * for details.
 *
 * This code is licensed to you under the terms of the Apache License, version
 * 2.0, or, at your option, the terms of the GNU General Public License,
 * version 2.0. See the APACHE20 and GPL2 files for the text of the licenses,
 * or the following URLs:
 * http://www.apache.org/licenses/LICENSE-2.0
 * http://www.gnu.org/licenses/gpl-2.0.txt
 *
 * If you redistribute this file in source form, modified or unmodified, you
 * may:
 *   1) Leave this header intact and distribute it under the same terms,
 *      accompanying it with the APACHE20 and GPL20 files, or
 *   2) Delete the Apache 2.0 clause and accompany it with the GPL2 file, or
 *   3) Delete the GPL v2 clause and accompany it with the APACHE20 file
 * In all cases you must keep the copyright notice intact and include a copy
 * of the CONTRIB file.
 *
 * Binary distributions must follow the binary distribution requirements of
 * either License.
 */

/** @file Protonect.cpp Main applicssation file. */

#include <iostream>
#include <cstdlib>
#include <signal.h>

/// [headers]
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>
/// [headers]

#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <GLFW/glfw3.h>

template<size_t TBytesPerPixel, GLenum TInternalFormat, GLenum TFormat, GLenum TType>
struct ImageFromat
{
    static const size_t BytesPerPixel = TBytesPerPixel;
    static const GLenum InternalFormat = TInternalFormat;
    static const GLenum Format = TFormat;
    static const GLenum Type = TType;
};

int main()
{
    const int framemax = 1;
    std::cout<<"start"<<std::endl;
    libfreenect2::Freenect2 freenect2;
    libfreenect2::Freenect2Device *dev = 0;
    libfreenect2::PacketPipeline *pipeline = 0;
    std::string serial = "";
    if(freenect2.enumerateDevices()==0){
        std::cout<<"no device connected!"<<std::endl;
        return -1;
    }
    if(serial==""){
        serial = freenect2.getDefaultDeviceSerialNumber();
    }
    if(pipeline){
        dev = freenect2.openDevice(serial, pipeline);
    }else{
        dev = freenect2.openDevice(serial);
    }
    if(dev==0){
        std::cout<<"failure opening device!"<<std::endl;
    }else{
        std::cout<<"open success: "<<dev<<std::endl;
    }
    
    //bool piccache_shutdown = false;
    int types = 0;
    types |= libfreenect2::Frame::Color;
    types |= libfreenect2::Frame::Ir | libfreenect2::Frame::Depth;
    libfreenect2::SyncMultiFrameListener listener(types);
    libfreenect2::FrameMap frames;
    dev->setColorFrameListener(&listener);
    dev->setIrAndDepthFrameListener(&listener);
    dev->start();
    std::cout<<"device serial: "<<dev->getSerialNumber()<<std::endl;
    std::cout<<"device firmware: "<<dev->getFirmwareVersion()<<std::endl;
    
    for(int i=0;i<framemax;i++){
        if(!listener.waitForNewFrame(frames, 10*1000)){
            std::cout<<"timeout!"<<std::endl;
            return -1;
        }
        libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
        libfreenect2::Frame *ir = frames[libfreenect2::Frame::Ir];
        libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];
        float w = static_cast<float>(rgb->width);
        float h = static_cast<float>(rgb->height);
        char *tem = (char*)malloc(rgb->width*rgb->height*rgb->bytes_per_pixel);
        std::cout<<"strlen "<<strlen(tem)<<std::endl;
        std::copy(rgb->data, rgb->data + rgb->width * rgb->height * rgb->bytes_per_pixel, tem);
        std::cout<<"strlen "<<strlen(tem)<<std::endl;
        // std::ofstream ofs;
        // ofs.open("rgb_f");
        FILE* fp = fopen("rgb_f", "w+");
        fwrite(tem, sizeof(char), 1920*1080*4, fp);
        fclose(fp);
        // for(int i=0;i<rgb->width*rgb->height*rgb->bytes_per_pixel;i++)
        //     ofs<<tem[i];
        
        listener.release(frames);
    }
    //dev->setLed(LED_RED);
    dev->stop();
    dev->close();
}
