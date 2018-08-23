/*
 *  Created by Phil Nash on 15/6/2018.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "catch_generators.hpp"
#include "catch_random_number_generator.h"
#include "catch_interfaces_capture.h"

#include <algorithm>
#include <numeric>
#include <limits>

namespace Catch {

IGeneratorTracker::~IGeneratorTracker() {}

namespace Generators {

    GeneratorBase::~GeneratorBase() {}

    std::vector<size_t> randomiseIndices( size_t selectionSize, size_t sourceSize ) {

        assert( selectionSize <= sourceSize );

        std::vector<size_t> indices( selectionSize );
        std::iota(indices.begin(), indices.end(), 0);

        // Plain old boring F-Y shuffle
        const auto swaps = std::min(selectionSize - 1, sourceSize - 2);
        for (size_t i = 0; i < swaps; ++i) {
            std::uniform_int_distribution<size_t> selectionRange(i, sourceSize - 1);
            auto swapIdx = selectionRange( rng() );
            std::swap(indices[i], indices[swapIdx]);
        }

        return indices;
    }

    auto acquireGeneratorTracker( SourceLineInfo const& lineInfo ) -> IGeneratorTracker& {
        return getResultCapture().acquireGeneratorTracker( lineInfo );
    }

    template<>
    auto all<int>() -> Generator<int> {
        return range( std::numeric_limits<int>::min(), std::numeric_limits<int>::max() );
    }

} // namespace Generators
} // namespace Catch
