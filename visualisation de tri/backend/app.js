const express = require('express');
const { exec } = require('child_process');
const path = require('path');

const app = express();
const port = 3000;

const cors = require('cors');
app.use(cors());

app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(express.static(path.join(__dirname, 'C:/Users/adeni/Downloads/projet_test_der/projet_test/backend/')));

app.post('/sort', (req, res) => {
  const inputData = req.body.inputValues.split(' ').map(Number);
  const sortType = req.query.sortType;

  let command = '';
  if (sortType === 'bubble') {
    command = path.join(__dirname, 'triabulle');
  } else if (sortType === 'dichotomy') {
    command = path.join(__dirname, 'dichotomie');
  } else if (sortType === 'quick') {
    command = path.join(__dirname, 'trirapide');
  } else if (sortType === 'insert') {
    command = path.join(__dirname, 'triparinsert');
  } else if (sortType === 'fusion') {
    command = path.join(__dirname, 'trifusion');
  } else if (sortType === 'pairimpair') {
    command = path.join(__dirname, 'tripairimpair');
  } else if (sortType === 'peigne') {
    command = path.join(__dirname, 'tripeigne');
  }


  exec(command + ' ' + inputData.join(' '), (error, stdout, stderr) => {
    console.log(command + ' ' + inputData.join(' '));
      if (error) {
          console.error(`Erreur lors de l'exécution du tri : ${error}`);
          return res.status(500).json({ error: 'Erreur lors du tri' });
      }

      const sortedSteps = stdout.split('\n').map(step => step.split(' ').map(Number));
      res.json({ steps: sortedSteps });

      // Exécuter le fichier Python tabimage.py
      const pythonCommandTabImage = 'python3 ' + path.join(__dirname, 'tabimage.py');
      exec(pythonCommandTabImage, (pythonErrorTabImage, pythonStdoutTabImage, pythonStderrTabImage) => {
          if (pythonErrorTabImage) {
              console.error(`Erreur lors de l'exécution de tabimage.py : ${pythonErrorTabImage}`);
          } else {
              // Exécuter le fichier Python gif2.py après tabimage.py
              const pythonCommandGif2 = 'python3 ' + path.join(__dirname, 'gif2.py');
              exec(pythonCommandGif2, (pythonErrorGif2, pythonStdoutGif2, pythonStderrGif2) => {
                  if (pythonErrorGif2) {
                      console.error(`Erreur lors de l'exécution de gif2.py : ${pythonErrorGif2}`);
                  }
              });
          }
      });
  });
});

app.listen(port, () => {
  console.log(`Backend en cours d'exécution sur le port ${port}`);
});
