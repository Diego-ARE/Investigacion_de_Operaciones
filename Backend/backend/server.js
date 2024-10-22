const express = require('express');
const { exec } = require('child_process');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();
const PORT = process.env.PORT || 3000;

// Configurar CORS
app.use(cors());
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

// Ruta para calcular
app.post('/calcular', (req, res) => {
    const { horasCarga, horasDescarga, horasOrganizacion, costoA, costoB, costoC } = req.body;

    exec(`asignacion.exe ${horasCarga} ${horasDescarga} ${horasOrganizacion} ${costoA} ${costoB} ${costoC}`, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error ejecutando el programa: ${error}`);
            return res.status(500).send('Error en el servidor');
        }

        // Filtrar la salida para obtener solo la parte JSON
        const jsonStartIndex = stdout.indexOf('{');
        const jsonEndIndex = stdout.lastIndexOf('}');
        
        if (jsonStartIndex !== -1 && jsonEndIndex !== -1) {
            const jsonString = stdout.substring(jsonStartIndex, jsonEndIndex + 1);
            try {
                const resultadoJson = JSON.parse(jsonString);
                res.json(resultadoJson); // Enviar el JSON parseado
            } catch (err) {
                console.error('Error al parsear la salida del programa:', err);
                res.status(500).send('Error procesando los datos');
            }
        } else {
            console.error('No se encontró un JSON válido en la salida');
            res.status(500).send('Error procesando los datos');
        }
    });
});



// Iniciar el servidor
app.listen(PORT, () => {
    console.log(`Servidor escuchando en http://localhost:${PORT}`);
});
