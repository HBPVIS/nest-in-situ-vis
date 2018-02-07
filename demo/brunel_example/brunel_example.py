
"""
Definition of spatially extended Brunel network.
This module provides layer and projections declarations suitable for
use with the NEST Topology Module.
It defines a Brunel-style network with neurons placed on a regular grid.
Connectivity is probabilitstic from the entire network, i.e., connectivity
is not structured spatially.
"""

from copy import deepcopy
from math import sqrt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

import nest
import nest.raster_plot
import nest.topology as tp


class Brunel3D:

    def __init__(self):
        self.layer_dict = {}
        # nest.SetKernelStatus({'print_time': True})

    class Parameters:
        """
        Define model parameters.
        """
        order = 9   # must be square
        NE = 4 * order  # number of excitatory neurons.
        NI = 1 * order  # number of inhibitory neurons

        lengthE = int(sqrt(NE))
        lengthI = int(sqrt(NI))

        if not (lengthE**2 == NE and lengthI**2 == NI):
            raise ValueError('Order must be a square number (order = n**2)')

        # neuron_model = 'iaf_psc_alpha'
        neuron_model = 'mat2_psc_exp'

        g = 5.0  # ratio inhibitory weight/excitatory weight
        eta = 2.0  # external rate relative to threshold rate
        epsilon = 0.1  # connection probability

        delay = 1.5  # synaptic delay in ms

        tauMem = 20.0  # time constant of membrane potential in ms
        theta = 20.0  # membrane threshold potential in mV

        J = 0.1  # postsynaptic amplitude in mV
        J_ex = J  # amplitude of excitatory postsynaptic potential
        J_in = -g * J_ex  # amplitude of inhibitory postsynaptic potential

        CE = int(epsilon * NE)  # number of excitatory synapses per neuron

        nu_th = theta / (J * CE * tauMem)
        nu_ex = eta * nu_th
        p_rate = 1.0 * nu_ex * CE

        neuron_params = {"C_m": 1.0,
                         "tau_m": tauMem,
                         "t_ref": 2.0,
                         "E_L": 0.0,
                         # "V_reset": 0.0,  # doesn't work with mat2_psc_exp
                         # "V_th": theta,  # doesn't work with mat2_psc_exp
                         "V_m": 0.0
                         }
        mm_params = {'record_from': ['V_m', 'V_th'],
                     'record_to': ['stream']}
        poisson_params = {"rate": p_rate}

    def modified_copy(self, orig, diff):
        """
        Returns a deep copy of dictionary with changes applied.
        @param orig  original dictionary, will be deep-copied
        @param diff  copy will be updated with this dict
        """

        tmp = deepcopy(orig)
        tmp.update(diff)
        return tmp

    def make_layer_specs(self):
        """
        Returns lists of dictionaries with model, layer, and synapse model
        specifications.
        """

        P = self.Parameters

        self.models = [(P.neuron_model, 'excitatory', P.neuron_params),
                       (P.neuron_model, 'inhibitory', P.neuron_params),
                       ('poisson_generator', 'noise', P.poisson_params),
                       ('multimeter', 'recordingNode', P.mm_params)]

        self.syn_models = [('static_synapse', 'static_excitatory', {})]

        dE = 1.0 / float(P.lengthE)
        limE = (1.0 - dE) / 2.0
        posE = np.linspace(-limE, limE, num=P.lengthE)

        dI = 1.0 / float(P.lengthI)
        limI = (1.0 - dI) / 2.0
        posI = np.linspace(-limI, limI, num=P.lengthI)

        self.layers = [('Excitatory', {'positions': [[x, y, 0.4]
                                                     for x in posE
                                                     for y in posE],
                                       'edge_wrap': True,
                                       'elements': 'excitatory'}),
                       ('Inhibitory', {'positions': [[x, y, -0.4]
                                                     for x in posI
                                                     for y in posI],
                                       'edge_wrap': True,
                                       'elements': 'inhibitory'})]
        self.layers.append(('PoissonGenerator',
                            {'positions': [[0.0, 0.0, 0.0]],
                             'elements': 'noise'}))
        self.layers.append(('Multimeter',
                            {'positions': [[0.0, 0.0, 0.0]],
                             'elements': 'recordingNode'}))
        self.layers.append(('SpikeDetector',
                            {'positions': [[0.0, 0.0, 0.0]],
                             'elements': 'spike_detector'}))

    def make_connection_specs(self):
        """
        Returns list of dictionaries specifying projections for Brunel network.
        """

        P = self.Parameters

        self.projections = [('Excitatory', 'Excitatory',
                             {'connection_type': 'convergent',
                              'synapse_model': 'static_synapse',
                              'kernel': P.epsilon,
                              'weights': P.J_ex,
                              'delays': P.delay}),
                            ('Excitatory', 'Inhibitory',
                             {'connection_type': 'convergent',
                              'synapse_model': 'static_synapse',
                              'kernel': P.epsilon,
                              'weights': P.J_ex,
                              'delays': P.delay}),
                            ('Inhibitory', 'Excitatory',
                             {'connection_type': 'convergent',
                              'synapse_model': 'static_synapse',
                              'kernel': P.epsilon,
                              'weights': P.J_in,
                              'delays': P.delay}),
                            ('Inhibitory', 'Excitatory',
                             {'connection_type': 'convergent',
                              'synapse_model': 'static_synapse',
                              'kernel': P.epsilon,
                              'weights': P.J_in,
                              'delays': P.delay}),
                            ('Multimeter', 'Excitatory',
                             {'connection_type': 'convergent'}),
                            ('Excitatory', 'SpikeDetector',
                             {'connection_type': 'convergent'}),
                            ('Inhibitory', 'SpikeDetector',
                             {'connection_type': 'convergent'}),
                            ('PoissonGenerator', 'Excitatory',
                             {'connection_type': 'convergent'})]

    def make_layers(self):
        # First, we copy the models with custom specifications
        # Neuron models
        for model in self.models:
            old_name, new_name, spec = model
            nest.CopyModel(old_name, new_name, spec)
        # Synapse models
        for model in self.syn_models:
            old_name, new_name, spec = model
            nest.CopyModel(old_name, new_name, spec)

        # Next we make the layers
        for l in self.layers:
            name = l[0]
            specs = l[1]
            self.layer_dict.update({name: tp.CreateLayer(specs)})

    def make_connections(self):
        # Connect layers
        for proj in self.projections:
            pre_layer = self.layer_dict[proj[0]]
            post_layer = self.layer_dict[proj[1]]
            conn_specs = proj[2]
            tp.ConnectLayers(pre_layer, post_layer, conn_specs)

    def simulate(self):
        nest.Simulate(1000)

    def plot_positions(self):
        ex_pos = self.layers[0][1]['positions']
        in_pos = self.layers[1][1]['positions']
        fig = plt.figure()
        ax = Axes3D(fig)
        for c, m, positions in [('b', 'o', ex_pos), ('r', '^', in_pos)]:
            ax.scatter([x for x, y, z in positions],
                       [y for x, y, z in positions],
                       [z for x, y, z in positions],
                       c=c, marker=m)

    def get_results(self):
        mm = (self.layer_dict['Multimeter'][0] + 1,)
        sd = (self.layer_dict['SpikeDetector'][0] + 1,)
        mm_status = nest.GetStatus(mm)[0]
        sd_status = nest.GetStatus(sd)[0]

        nest.raster_plot.from_device(sd, hist=True)

        senders = mm_status['events']['senders']
        times = mm_status['events']['times']
        v_m = mm_status['events']['V_m']
        v_th = mm_status['events']['V_th']
        step = int(max(senders)/100 + 1)  # Only plot results from some GIDs

        mm_events = []
        for i in range(1, max(senders) + 1, step):
            if i in senders:
                indices = np.argwhere(senders == i)
                mm_events.append({'GID': i,
                      'times': [times[n] for n in indices],
                      'V_m': [v_m[n] for n in indices],
                      'V_th': [v_th[n] for n in indices]})

        return {'multimeter': mm_events,
                'spike_detector': nest.GetStatus(sd)[0]}


if __name__ == '__main__':
    nest.ResetKernel()

    print('Making specifications')
    brunel = Brunel3D()
    brunel.make_layer_specs()
    brunel.make_connection_specs()

    print('Making layers')
    brunel.make_layers()
    nest.topology.DumpLayerNodes([l[0] for l in brunel.layer_dict.values()][:2],
                                     'brunel_nodes.txt')

    print('Making connections')
    brunel.make_connections()

    brunel.simulate()

    print('Getting results')
    brunel.plot_positions()
    results = brunel.get_results()

    for value in ['V_m', 'V_th']:
        plt.figure()
        for n in results['multimeter'][::20]:
            plt.plot(n['times'], n[value], label='{}'.format(n['GID']))
            plt.legend()
        plt.title(value)
    plt.show()
