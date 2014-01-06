/*
 * INTEL CONFIDENTIAL
 *
 * Copyright 2013 Intel Corporation
 * All Rights Reserved.
 *
 * The source code contained or described herein and all documents related
 * to the source code ("Material") are owned by Intel Corporation or its
 * suppliers or licensors.
 * Title to the Material remains with Intel Corporation or its suppliers and
 * licensors. The Material contains trade secrets and proprietary and
 * confidential information of Intel or its suppliers and licensors.
 * The Material is protected by worldwide copyright and trade secret laws and
 * treaty provisions. No part of the Material may be used, copied, reproduced,
 * modified, published, uploaded, posted, transmitted, distributed, or
 * disclosed in any way without Intel's prior express written permission.
 * No license under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or delivery
 * of the Materials, either expressly, by implication, inducement, estoppel or
 * otherwise. Any license under such intellectual property rights must be
 * express and approved by Intel in writing.
 */

#pragma once

namespace audio_comms
{
namespace cme
{
namespace serializer
{

/** Setter helper
 * Transforms a method setter to a function setter.
 * If M is already a function setter forwards it.
 */
template <class M, M m>
struct SetterHelper;

// Method setter
template <class Ret, class Class, class Arg, Ret(Class::*setter) (Arg)>
struct SetterHelper<Ret(Class::*) (Arg), setter>
{
    typedef Ret (*type) (Class &, Arg);
    static Ret function(Class &instance, Arg arg)
    {
        return (instance.*setter)(arg);
    }
};

// Const method setter
template <class Ret, class Class, class Arg, Ret(Class::*setter) (Arg)const>
struct SetterHelper<Ret(Class::*) (Arg)const, setter>
{
    typedef Ret (*type) (const Class &, Arg);
    static Ret function(const Class &instance, Arg arg)
    {
        return (instance.*setter)(arg);
    }
};

// Function setter
template <class Ret, class Class, class Arg, Ret(*setter) (Class, Arg)>
struct SetterHelper<Ret (*)(Class, Arg), setter>
{
    typedef Ret (*type) (Class &, Arg);
    static Ret function(Class &instance, Arg arg)
    {
        return (*setter)(instance, arg);
    }
};

} // namespace serializer
} // namespace cme
} // namespace audio_comms