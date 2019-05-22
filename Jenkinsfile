pipeline {
  agent any
  stages {
    stage('stage1') {
      parallel {
        stage('stage1') {
          steps {
            echo 'test pipeline stage1'
          }
        }
        stage('stage2') {
          steps {
            echo 'stage 2 test'
          }
        }
      }
    }
    stage('stage3') {
      parallel {
        stage('stage3') {
          steps {
            echo 'stage3 test'
          }
        }
        stage('stage5') {
          steps {
            echo 'stage5 test'
          }
        }
      }
    }
    stage('stage6') {
      steps {
        echo 'stage6 test'
      }
    }
  }
  environment {
    ENV_TEST1 = '1'
  }
}