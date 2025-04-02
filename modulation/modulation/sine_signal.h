#ifndef SINE_SIGNAL_H
#define SINE_SIGNAL_H

#include <cmath>
#include <vector>
#include <numeric>
#include <deque>
#include <random>
#include <armadillo>



struct iir_filter
{
    std::vector<double> a;
    std::vector<double> b;

    std::deque<double> last_values;
    std::deque<double> last_filtered_values;

    double operator()(double v)
    {
        last_values.push_back(v);
        last_values.pop_front();
        double fv = inner_product(last_values.begin(),last_values.end(),b.begin(),0.0) + inner_product(last_filtered_values.begin(),last_filtered_values.end(),a.begin(),0.0);
        last_filtered_values.push_back(v);
        last_filtered_values.pop_front();
        return fv;
    }

    template <typename InputIt, typename T = int>
    std::vector<T> operator() (InputIt begin, InputIt end)
    {
        std::vector<T> v(end - begin);
        for (auto i = 0; i != end - begin; ++i)
        {
            v[i] = this->operator ()(*(begin + i));
            // v[i] = *(begin + i);
        }
        return v;
    }
    template <typename ContainerIn, typename ContainerOut>
    ContainerOut filter(ContainerIn c)
    {
        ContainerOut c_o(std::size(c));
        for (auto i = 0; i < std::size(c); ++i)
            c_o[i] = this->operator ()(*(std::begin(c)+ i));
        return c_o;
    }
};



class sine_signal
{
public:
    sine_signal();

    double A{1}, f{1}, phase{0}, fd{1024};

    int operator() ()
    {
        phase += 2*M_PI*f/fd;
        if (phase >= 2*M_PI) phase -= 2*M_PI;
        return 32768/2. *A*sin(phase);
    }

    std::vector<int> operator() (size_t n)
    {
        std::vector<int> v(n);

        for (auto i = 0; i< n ; ++i)
        {
            v[i] = this->operator()();
        }

        return v;
    }
};

class PM_signal
{
    int phase_states = 2;
    int vector_step = 1;
    std::random_device rd;
    std::normal_distribution<double> noise_dist{0,10};

public:
    double A{1}, f{1}, phase{0}, fd{1024}, symbol_speed{10};

    iir_filter f1{{0.047,0.094,0.047},{1.324,-0.78},{0,0,0},{0,0}};
    iir_filter f2{{0.5,-1.0,0.5},{1.453,-0.803},{0,0,0},{0,0}};
    iir_filter f3{{0.031,0.063,0.031},{1.313,-0.897},{0,0,0},{0,0}};
    iir_filter f4{{0.250,-0.5,0.250},{1.614,-0.921},{0,0,0},{0,0}};


    std::vector<short> operator() (std::vector<bool> v)
    {
        double symbol_step_n = fd/symbol_speed;
        std::vector<int> samples(v.size()/vector_step * symbol_step_n);

        for (auto i = 0; i < samples.size(); ++i)
        {
            phase += 2*M_PI*f/fd;
            if (phase >= 2*M_PI) phase -= 2*M_PI;

            size_t index = i * vector_step / symbol_step_n;
            index = index - (index % vector_step);

            int state = convert_bits_to_state(v,index);

            if (phase_states == 4)
            {
                samples[i] = 32767/2. * A *sin(phase + 2 * M_PI * state / double(phase_states)/* + M_PI_4f*/);
            }
            else
                samples[i] = 32767/2. * A *sin(phase + 2 * M_PI * state / double(phase_states));

            // samples[i] += noise_dist(rd);
        }


        samples = f1(samples.begin(),samples.end());
        samples = f2(samples.begin(),samples.end());
        samples = f3(samples.begin(),samples.end());
        samples = f4(samples.begin(),samples.end());

        std::vector<short> s_v(samples.size());
        std::copy(samples.begin(),samples.end(),s_v.begin());

        return s_v;
    }

    int convert_bits_to_state(std::vector<bool>& v, int index)
    {
        if (phase_states == 2)
            return v[index] ? 1:0;
        else if (phase_states == 4)
        {
            int a = (v[index] << 1) + v[index + 1];

            switch(a)
            {
                // gray code
            case 0b11: return 0; break;
            case 0b01: return 1; break;
            case 0b00: return 2; break;
            case 0b10: return 3; break;
            }
        }
    }

    void set_phase_states(int size)
    {
        phase_states = size;
        vector_step = round(log2(size));
    }
};


struct PM_demodulator
{
    double f,fd;
    double phase = 0;
    double bit_speed;

    iir_filter f1 = {
        {0.99381445,-1.99363155,0.9851314,-1.985046},{2,1,2},{0,0,0,0},{0,0,0}
    };
    iir_filter f2 = f1;
    iir_filter f3 = f1;

    template <typename InputIt>
    auto operator()(InputIt begin, InputIt end)
    {
        std::vector<int> v_sin(end - begin);
        std::vector<int> v_cos(end - begin);
        std::vector<double> v(end - begin);

        for (auto i = 0; i < v_sin.size(); ++i)
        {
            v_sin[i] = *(begin + i) * sin(2*M_PI*f*i/fd + phase);
            v_cos[i] = *(begin + i) * cos(2*M_PI*f*i/fd + phase);

            // v[i] = double(v_sin[i] * v_cos[i]) / std::numeric_limits<int>::max();
            // v[i] = v_sin[i] * v_cos[i];
        }

        auto v_sin_f = f1(v_sin.begin(),v_sin.end());
        auto v_cos_f = f2(v_cos.begin(),v_cos.end());

        for (auto i = 0; i < v_sin.size(); ++i)
        {
            v[i] = double(v_sin_f[i] * v_cos_f[i]) / std::numeric_limits<int>::max();
        }

        std::vector<double> v_ = f3.filter<std::vector<double>,std::vector<double>>(v);
        // double a = std::accumulate(v_.begin(),v_.end(),0)/double(v_.size());
        phase += 0.01 * v_[10];

        // phase -= 0.5 * a;
        // phase = fmod(phase,2*M_PI);

        return std::vector{v_sin_f,v_cos_f};
    }
};



#endif // SINE_SIGNAL_H
