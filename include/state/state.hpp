#pragma once

#include <iostream>

#include <Eigen/Dense>

#include "dimensions.hpp"

using namespace Eigen;

template <class ...Dimensions>
class State {
    public:
        /**
         * @brief Construct a new State
         * 
         * @param dimensions 
         */
        State(Dimensions... dimensions)
        : data_(VectorXd::Zero(getDimension())), format_(StreamPrecision, DontAlignCols, ",", ",", "", "", "", "")
        {
            std::tuple<Dimensions...> dimensions_tuple{dimensions...};
            unpack(dimensions_tuple);
        }
        
        /**
         * @brief Format output of the state vector
         * 
         * @param output output stream to output on
         * @param state state vector to be outputted
         * @return output stream with added state vector output
         */
        friend std::ostream &operator<<( std::ostream &output, const State &state) {
            output << state.data_.format(state.format_);
            return output;
        }

        /**
         * @brief Get the Dimension of the State
         * 
         * @return size_t number of dimensions
         */
        size_t getDimension() {
            return std::tuple_size<std::tuple<Dimensions...>>::value;
        }

        /**
         * @brief Base case if no parameter is left in parameter pack
         * 
         * @tparam I parameter index
         * @param tuple tuple containing all parameters
         * @return after last index was processed
         */
        template<size_t I = 0>
        typename std::enable_if<I == sizeof...(Dimensions), void>::type unpack(std::tuple<Dimensions...> tuple) {
            return;
        }

        /**
         * @brief Recursively unpack parameter pack for every parameter index
         * 
         * @tparam I parameter index
         */
        template<size_t I = 0>
        typename std::enable_if<I < sizeof...(Dimensions), void>::type unpack(std::tuple<Dimensions...> tuple) {
            data_[I] = std::get<I>(tuple).value;
            unpack<I + 1>(tuple);
        }

    private:
        VectorXd data_;
        IOFormat format_;

};