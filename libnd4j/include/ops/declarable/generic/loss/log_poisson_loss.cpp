/*******************************************************************************
 * Copyright (c) 2015-2018 Skymind, Inc.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License, Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/

//
//  @author raver119@gmail.com
//

#include <op_boilerplate.h>
#if NOT_EXCLUDED(OP_log_poisson_loss)

#include <ops/declarable/CustomOperations.h>

namespace nd4j {
namespace ops {

    CONFIGURABLE_OP_IMPL(log_poisson_loss, 2, 1, true, 0, 0) {
        auto input = INPUT_VARIABLE(0);
        auto targets = INPUT_VARIABLE(1);
        bool computeFullLoss = false;

        if (block.numI() > 0)
            computeFullLoss = INT_ARG(0) != 0;
        
        REQUIRE_TRUE(targets->isSameShape(input), 0, "log_poisson_loss: The shape of both input params should be equal.");

        auto output = OUTPUT_VARIABLE(0);
        if (!computeFullLoss)
            targets->applyPairwiseTransform(pairwise::LogPoissonLoss, input, output, nullptr);
        else
            targets->applyPairwiseTransform(pairwise::LogPoissonLossFull, input, output, nullptr);

        return Status::OK();
    }

    DECLARE_TYPES(log_poisson_loss) {
        getOpDescriptor()
                ->setAllowedInputTypes(nd4j::DataType::ANY)
                ->setAllowedOutputTypes(DataType::BOOL);
    }
}
}

#endif