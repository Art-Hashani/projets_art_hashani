function sortValues() {
  const inputValues = document.getElementById('inputValues').value;
  const sortingType = document.getElementById('sortingType').value; // Récupérer le type de tri sélectionné
  
  let url = 'http://localhost:3000/sort';
  if (sortingType === 'bubble') {
      url += '?sortType=bubble'; // Ajouter un paramètre pour spécifier le tri à bulles
  } else if (sortingType === 'dichotomy') {
      url += '?sortType=dichotomy'; // Ajouter un paramètre pour spécifier le tri par dichotomie
  } else if (sortingType === 'quick') {
      url += '?sortType=quick';
  } else if (sortingType === 'insert') {
    url += '?sortType=insert';
  } else if (sortingType === 'pairimpair') {
    url += '?sortType=pairimpair';
  } else if (sortingType === 'peigne') {
    url += '?sortType=peigne';
  }

  
  fetch(url, {
      method: 'POST',
      headers: {
          'Content-Type': 'application/json'
      },
      body: JSON.stringify({ inputValues })
  })
  .then(response => response.json())
  .then(data => visualizeSorting(data.steps))
  .catch(error => console.error('Erreur :', error));
}

  
function visualizeSorting(steps) {
  const visualizationDiv = document.getElementById('visualization');
  visualizationDiv.innerHTML = ''; // Effacer le contenu précédent

  steps.forEach((step, index) => {
    setTimeout(() => {
      const stepDiv = document.createElement('div');
      stepDiv.textContent = `Étape ${index + 1}: ${step}`;
      visualizationDiv.appendChild(stepDiv);
    }, index * 1000); // Changer la vitesse de visualisation en ajustant la valeur du délai (ici, 1000 ms = 1 seconde)
  });
}
  