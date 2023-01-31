/**
 *  @file
 *  @brief Implementation of TfConverter
 *
 *  ___    ___
 *  \  \  /  /
 *   \  \/  /   Fixposition AG
 *   /  /\  \   All right reserved.
 *  /__/  \__\
 *
 */

/* SYSTEM / STL */
#include <iostream>

/* PACKAGE */
#include <fixposition_driver_lib/converter/tf.hpp>

namespace fixposition {

/// msg field indices
static constexpr const int msg_type_idx = 1;
static constexpr const int msg_version_idx = 2;
static constexpr const int from_frame_idx = 3;
static constexpr const int to_frame_idx = 4;
static constexpr const int translation_x_idx = 5;
static constexpr const int translation_y_idx = 6;
static constexpr const int translation_z_idx = 7;
static constexpr const int orientation_w_idx = 8;
static constexpr const int orientation_x_idx = 9;
static constexpr const int orientation_y_idx = 10;
static constexpr const int orientation_z_idx = 11;

void TfConverter::ConvertTokens(const std::vector<std::string>& tokens) {
    if (tokens.size() != 12) {
        std::cout << "Error in parsing TF string with " << tokens.size() << " fields! TFs will be empty.\n";
        msg_ = TfData();
        return;
    }
    // header stamps
    msg_.frame_id = "FP_" + tokens.at(from_frame_idx);
    msg_.child_frame_id = "FP_" + tokens.at(to_frame_idx);

    msg_.translation =
        Vector3ToEigen(tokens.at(translation_x_idx), tokens.at(translation_y_idx), tokens.at(translation_z_idx));
    msg_.rotation = Vector4ToEigen(tokens.at(orientation_w_idx), tokens.at(orientation_x_idx),
                                   tokens.at(orientation_y_idx), tokens.at(orientation_z_idx));

    // process all observers
    for (auto& ob : obs_) {
        ob(msg_);
    }
}

}  // namespace fixposition