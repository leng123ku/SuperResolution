// Copyright (c) 2012, Vladislav Vinogradov (jet47)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the <organization> nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#ifndef __SUPER_RESOLUTION_HPP__
#define __SUPER_RESOLUTION_HPP__

#include <vector>
#include <opencv2/core/core.hpp>

#if defined WIN32 || defined _WIN32 || defined WINCE
#   if defined SUPER_RESOLUTION_SHARED
#       define SUPER_RESOLUTION_EXPORTS __declspec(dllexport)
#   else
#       define SUPER_RESOLUTION_EXPORTS __declspec(dllimport)
#   endif
#else
#   define SUPER_RESOLUTION_EXPORTS
#endif

class SUPER_RESOLUTION_EXPORTS SuperResolution : public cv::Algorithm
{
public:
    enum Method
    {
        EXAMPLE_BASED,
        METHOD_MAX
    };

    static cv::Ptr<SuperResolution> create(Method method);

    virtual ~SuperResolution();

    virtual void train(const std::vector<cv::Mat>& images) = 0;
    virtual void train(const cv::Mat& image);
    template <class Iter> void train(Iter begin, Iter end);

    virtual void clear() = 0;

    virtual void process(const cv::Mat& src, cv::Mat& dst) = 0;
};

template <class Iter>
void SuperResolution::train(Iter begin, Iter end)
{
    std::vector<cv::Mat> images(begin, end);
    train(images);
}

#endif // __SUPER_RESOLUTION_HPP__
