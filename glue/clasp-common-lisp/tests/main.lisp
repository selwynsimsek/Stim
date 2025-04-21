(defpackage stim/tests/main
  (:use :cl
        :stim
        :rove))
(in-package :stim/tests/main)

;; NOTE: To run this test file, execute `(asdf:test-system :stim)' in your Lisp.

(deftest test-target-1
  (testing "should (= 1 1) to be true"
    (ok (= 1 1))))
