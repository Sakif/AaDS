#ifndef C_ACTION_POINT_HPP
#define C_ACTION_POINT_HPP

struct c_action_point
{
  double current, max, refill_rate;

  void refill();
  bool sufficient_points_to_complete(const double cost) const;
};

#endif
