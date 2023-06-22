enum TEST_TYPE {
  TEST,
  MIDTERM,
  PROJECT,
  FINAL,
};

const double TEST_WEIGHTS [4] {
  0.10,
  0.25,
  0.25,
  0.30,
};

struct EXAM {
  TEST_TYPE test_type;
  double test_weight;
};

const EXAM test = { TEST, TEST_WEIGHTS[0] };
const EXAM midterm = { TEST, TEST_WEIGHTS[0] };


double calc_grade(int mark) { return (mark / 100.0); }

double calc_test_mark(int mark) {

}
double calc_midterm_exam_mark() { }
double calc_final_exam_mark() { }
double calc_project_mark() { }
double calc_final_mark() { }

int main() {
  return 0;
}
