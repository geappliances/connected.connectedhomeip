/*
 *
 *    Copyright (c) 2023 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

namespace chip {
namespace app {
namespace Clusters {

using namespace chip::app::Clusters::EnergyEvse;

/* This callbacks mechanism is intended to allow different delegates to
 * dispatch notifications that something has changed.
 *
 * This is not specific to the EnergyEVSE cluster, but includes DeviceEnergyManagement
 * and potential future clusters.
 */
enum EVSECallbackType
{
    /*
     * The State has changed (e.g. from Disabled to Charging, or vice-versa)
     */
    StateChanged,
    /*
     * ChargeCurrent has changed
     */
    ChargeCurrentChanged,
    /*
     * Charging Preferences have changed
     */
    ChargingPreferencesChanged,
    /*
     * DeviceEnergyManagement has changed
     */
    DeviceEnergyManagementChanged,
};

struct EVSECbInfo
{
    EVSECallbackType type;

    union
    {
        /* for type = StateChanged */
        struct
        {
            StateEnum state;
            SupplyStateEnum supplyState;
        } StateChange;

        /* for type = ChargeCurrentChanged */
        struct
        {
            int64_t maximumChargeCurrent;
        } ChargingCurrent;
    };
};

typedef void (*EVSECallbackFunc)(const EVSECbInfo * cb, intptr_t arg);

struct EVSECallbackWrapper
{
    EVSECallbackFunc handler;
    intptr_t arg;
};

} // namespace Clusters
} // namespace app
} // namespace chip
