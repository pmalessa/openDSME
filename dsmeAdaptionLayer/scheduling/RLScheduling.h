/*
 * openDSME
 *
 * Implementation of the Deterministic & Synchronous Multi-channel Extension (DSME)
 * introduced in the IEEE 802.15.4e-2012 standard
 *
 * Authors: Florian Meier <florian.meier@tuhh.de>
 *          Maximilian Koestler <maximilian.koestler@tuhh.de>
 *          Sandrina Backhauss <sandrina.backhauss@tuhh.de>
 *
 * Based on
 *          DSME Implementation for the INET Framework
 *          Tobias Luebkert <tobias.luebkert@tuhh.de>
 *
 * Copyright (c) 2015, Institute of Telematics, Hamburg University of Technology
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef RLSCHEDULING_H_
#define RLSCHEDULING_H_

#include "GTSScheduling.h"
#include "../NeuralNetwork.h"
#include "../DSMEAdaptionLayer.h"


namespace dsme {

class DSMEAdaptionLayer;

class RLScheduling : public GTSSchedulingImpl<GTSSchedulingData, GTSRxData> {
public:
    RLScheduling(DSMEAdaptionLayer& dsmeAdaptionLayer) : action(0), lastAction(0), GTSSchedulingImpl(dsmeAdaptionLayer) {
    }

    virtual GTSSchedulingDecision getNextSchedulingAction(uint16_t address) override;
    virtual void multisuperframeEvent() {};
private:
    NeuralNetwork<float> network;
    uint8_t action;
    uint8_t lastAction;
    
    uint8_t toActionID(const uint8_t slotID, const uint8_t superframeID) const;
    void fromActionID(const uint8_t actionID, uint8_t &slotID, uint8_t &superframeID) const;
    
    void observeState(float *state, uint8_t numStates) const;
    void logState(float *state, uint8_t numStates) const;     

    GTSSchedulingDecision allocateSlot(uint16_t address) const;
    GTSSchedulingDecision deallocateSlot(uint16_t address) const;

    void blockSuperframe(float *state, const uint8_t actionID) const;
};  

} /* namespace dsme */

#endif /* RLSCHEDULING_H_ */