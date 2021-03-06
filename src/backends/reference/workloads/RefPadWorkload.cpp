//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include "RefPadWorkload.hpp"

#include "Pad.hpp"
#include "RefWorkloadUtils.hpp"

#include "Profiling.hpp"

#include <ResolveType.hpp>

#include <vector>

namespace armnn
{

template <armnn::DataType DataType>
void RefPadWorkload<DataType>::Execute() const
{
    using T = ResolveType<DataType>;

    ARMNN_SCOPED_PROFILING_EVENT(Compute::CpuRef, "RefPadWorkload_Execute");

    const TensorInfo& inputInfo = GetTensorInfo(m_Data.m_Inputs[0]);
    const TensorInfo& outputInfo = GetTensorInfo(m_Data.m_Outputs[0]);

    const T* inputData = GetInputTensorData<T>(0, m_Data);
    T* outputData = GetOutputTensorData<T>(0, m_Data);

    Pad(inputInfo, outputInfo, m_Data.m_Parameters.m_PadList, inputData, outputData, m_Data.m_Parameters.m_PadValue);
}

template class RefPadWorkload<DataType::BFloat16>;
template class RefPadWorkload<DataType::Float32>;
template class RefPadWorkload<DataType::Float16>;
template class RefPadWorkload<DataType::QAsymmS8>;
template class RefPadWorkload<DataType::QAsymmU8>;
template class RefPadWorkload<DataType::QSymmS16>;

} //namespace armnn