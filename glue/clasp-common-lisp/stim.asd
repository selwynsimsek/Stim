(defsystem "stim"
  :version "0.0.1"
  :author "Selwyn Simsek"
  :mailto "selwyn.simsek@cantab.net"
  :license ""
  :depends-on ("cffi")
  :components ((:module "src"
                :components
                ((:file "main"))))
  :description ""
  :in-order-to ((test-op (test-op "stim/tests"))))

(defsystem "stim/tests"
  :author "Selwyn Simsek"
  :license ""
  :depends-on ("stim"
               "rove")
  :components ((:module "tests"
                :components
                ((:file "main"))))
  :description "Test system for stim"
  :perform (test-op (op c) (symbol-call :rove :run c)))
