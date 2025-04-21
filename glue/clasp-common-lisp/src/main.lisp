(uiop:define-package stim
  (:use #:cl))
(in-package #:stim)

#-clasp (error "This is a clasp-only library!")

(eval-when (:load-toplevel)
  (let ((build-directory (truename (asdf:system-relative-pathname :stim #p"../../build/out")))
        (glue-directory (asdf:system-relative-pathname :stim #p"./src/")))
    (uiop:run-program (format nil "cd ~a && make clean && make" glue-directory)
                      :force-shell t :output *error-output*
                      :error-output *error-output*)
    ;; Rebuild glue code on loading the library


    ;; Now load the foreign library

    (cffi:load-foreign-library #+darwin "libstimclasp.dylib"
                               #-darwin "libstimclasp.so"
                               :search-path glue-directory)))

