/*
 *
 * This file is part of the open-source SeetaFace engine, which includes three modules:
 * SeetaFace Detection, SeetaFace Alignment, and SeetaFace Identification.
 *
 * This file is part of the SeetaFace Detection module, containing codes implementing the
 * face detection method described in the following paper:
 *
 *
 *   Funnel-structured cascade for multi-view face detection with alignment awareness,
 *   Shuzhe Wu, Meina Kan, Zhenliang He, Shiguang Shan, Xilin Chen.
 *   In Neurocomputing (under review)
 *
 *
 * Copyright (C) 2016, Visual Information Processing and Learning (VIPL) group,
 * Institute of Computing Technology, Chinese Academy of Sciences, Beijing, China.
 *
 * The codes are mainly developed by Shuzhe Wu (a Ph.D supervised by Prof. Shiguang Shan)
 *
 * As an open-source face recognition engine: you can redistribute SeetaFace source codes
 * and/or modify it under the terms of the BSD 2-Clause License.
 *
 * You should have received a copy of the BSD 2-Clause License along with the software.
 * If not, see < https://opensource.org/licenses/BSD-2-Clause>.
 *
 * Contact Info: you can send an email to SeetaFace@vipl.ict.ac.cn for any problems.
 *
 * Note: the above information must be kept whenever or wherever the codes are used.
 *
 */

#ifndef SEETA_FD_UTIL_IMAGE_PYRAMID_H_
#define SEETA_FD_UTIL_IMAGE_PYRAMID_H_

#include <cstdint>
#include <string>
#include <cstring>

#include "common.h"

namespace seeta {
namespace fd {

void ResizeImage(const seeta::ImageData & src, seeta::ImageData* dest);

class ImagePyramid {
 public:
  ImagePyramid()
      : max_scale_(1.0f), min_scale_(1.0f),
        scale_factor_(1.0f), scale_step_(0.8f),
        width1x_(0), height1x_(0),
        width_scaled_(0), height_scaled_(0),
        buf_img_width_(2), buf_img_height_(2),
        buf_scaled_width_(2), buf_scaled_height_(2) {
    buf_img_ = new uint8_t[buf_img_width_ * buf_img_height_];
    buf_img_scaled_ = new uint8_t[buf_scaled_width_ * buf_scaled_height_];
  }

  ~ImagePyramid() {
    delete[] buf_img_;
    buf_img_ = nullptr;

    buf_img_width_ = 0;
    buf_img_height_ = 0;

    delete[] buf_img_scaled_;
    buf_img_scaled_ = nullptr;

    buf_scaled_width_ = 0;
    buf_scaled_height_ = 0;

    img_scaled_.data = nullptr;
    img_scaled_.width = 0;
    img_scaled_.height = 0;
  }

  inline void SetScaleStep(float step) {
    if (step > 0.0f && step <= 1.0f)
      scale_step_ = step;
  }

  inline void SetMinScale(float min_scale) {
    min_scale_ = min_scale;
  }

  inline void SetMaxScale(float max_scale) {
    max_scale_ = max_scale;
    scale_factor_ = max_scale;
    UpdateBufScaled();
  }

  void SetImage1x(const uint8_t* img_data, int32_t width, int32_t height);

  inline float min_scale() const { return min_scale_; }
  inline float max_scale() const { return max_scale_; }

  inline seeta::ImageData image1x() {
    seeta::ImageData img(width1x_, height1x_, 1);
    img.data = buf_img_;
    return img;
  }

  const seeta::ImageData* GetNextScaleImage(float* scale_factor = nullptr);

 private:
  void UpdateBufScaled();

  float max_scale_;
  float min_scale_;

  float scale_factor_;
  float scale_step_;

  int32_t width1x_;
  int32_t height1x_;

  int32_t width_scaled_;
  int32_t height_scaled_;

  uint8_t* buf_img_;
  int32_t buf_img_width_;
  int32_t buf_img_height_;

  uint8_t* buf_img_scaled_;
  int32_t buf_scaled_width_;
  int32_t buf_scaled_height_;

  seeta::ImageData img_scaled_;
};

}  // namespace fd
}  // namespace seeta

#endif  // SEETA_FD_UTIL_IMAGE_PYRAMID_H_
