struct
{
        /*
         * R - noise covariance
         * H - map scalar
         * k - kals gain
         * p - error estimate
         * x_hate - estimated value (return)
         * Q - estimated covariance
         */
        float _pos = 0.0;  
        float _vel = 0.0;
        float _acc = 0.0;
}global;
